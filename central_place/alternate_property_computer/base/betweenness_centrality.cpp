#include "betweenness_centrality.h"
#include "parallel_for.h"

#include <stdexcept>
#include <stack>
#include <queue>

#define MULTIPLE_TYPEDEF MULTIPLE_TYPEDEF2

namespace
{

class StepExecutor
{
    typedef graph_types::vertex             vertex;
    typedef std::vector<int>                Distances;
    MULTIPLE_TYPEDEF(std::vector<vertex>,   VertexPredecessors,
                                            ShortestPathCounts);

    typedef std::vector<double>             Dependencies;
    typedef std::vector<VertexPredecessors> VertexPredecessorsCollection;
    typedef std::stack<vertex>              ReachableVertices;

    typedef Base::BC::ResultType            ResultType;
    typedef std::lock_guard<std::mutex>     Lock;

    struct StepInfo
    {
        StepInfo(const ResultType& res)
            : vpc_(res.size())
            , spc_(res.size(), 0u)
            , d_(res.size(), -1)
            , deps_(res.size(), 0.0)
        {}

        VertexPredecessorsCollection vpc_;
        Dependencies deps_;
        ShortestPathCounts spc_;
        Distances d_;
    };
public:
    typedef unsigned long   IndexType;

public:
    StepExecutor(const graph_types::graph& g, ResultType& res)
        : res_(res)
        , g_(g)
        , info_(res)
    {}

    void prepare()
    {
        info_ = StepInfo(res_);
    }

    void operator()(IndexType index)
    {
        ReachableVertices s;
        info_.spc_[index] = 1u;
        info_.d_[index] = 0;

        std::queue<vertex> verticesToVisit;
        verticesToVisit.push(index);

        while (!verticesToVisit.empty())
        {
            const vertex v = verticesToVisit.back();
            verticesToVisit.pop();
            s.push(v);

            const auto neighbors = g_.neighbors_sequence(v);
            MT::parallel_for(0, neighbors.size() - 1, [&](IndexType i){
                    const vertex w = neighbors[i];
                    auto& distance = info_.d_[w];
                    const auto& possibleDistance = info_.d_[v] + 1;
                    // w found for the first time?
                    // critical section
                    {
                        Lock l (mutex_);
                        if (distance < 0)
                        {
                            verticesToVisit.push(w);
                            distance = possibleDistance;
                        }
                        // shortest path to w via v?
                        if (distance == possibleDistance)
                        {
                            info_.spc_[w] += info_.spc_[v];
                            info_.vpc_[w].push_back(v);
                        }
                    }
            });
        }
        // $s returns vertices in order of
        // non-increasing distance from $index
        while (!s.empty())
        {
            const vertex w = s.top();
            s.pop();
            for (auto& v : info_.vpc_[w])
            {
                info_.deps_[v] += (info_.spc_[v] / info_.spc_[w]) * (1 + info_.deps_[w]);
            }
            if (w != index)
            {
                res_[w] += info_.deps_[w];
            }
        }
    }

private:
    ResultType& res_;
    const graph_types::graph& g_;
    std::mutex mutex_;

    StepInfo info_;
};

}

namespace Base
{

void
BC::computeImpl()
{
    const auto size = graph_.size();

    StepExecutor exec(graph_, results_);

    MT::parallel_for(0, size - 1, [&](StepExecutor::IndexType index) {
        exec.prepare();
        exec(index);
    });
}

alternate_property_type
BC::typeImpl() const
{
    return BETWEENNESS_CENTRALITY;
}

BC::ResultType
BC::getDistributionImpl() const
{
    throw std::logic_error("Property Distribution is meaningless for BetweennessCentrality");
    return ResultType();
}

}

#include "betweenness_centrality.h"
#include "parallel_for.h"
#include "graph.h"
#include "utility.h"

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

    struct StepInfo
    {
        StepInfo(const BC::ResultCollection& res)
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
    StepExecutor(const graph_types::graph& g, BC::ResultCollection& res)
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
                    if (distance < 0)
                    {
                        verticesToVisit.push(w);
                        distance = possibleDistance;
                    }
                    if (distance == possibleDistance)
                    {
                        info_.spc_[w] += info_.spc_[v];
                        info_.vpc_[w].push_back(v);
                    }
            });
        }
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
    BC::ResultCollection& res_;
    const graph_types::graph& g_;

    StepInfo info_;
};

}

BC::ResultCollection
BC::calculate(const graph_types::graph& g)
{
    const auto size = g.size();
    if (0u == size)
        return ResultCollection();

    ResultCollection res (size, 0.0);
    StepExecutor exec(g, res);

    MT::parallel_for(0, size - 1, [&](StepExecutor::IndexType index) {
        exec.prepare();
        exec(index);
    });
    return res;
}



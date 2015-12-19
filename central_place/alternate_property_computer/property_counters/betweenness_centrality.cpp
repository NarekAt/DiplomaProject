#include "betweenness_centrality.h"
#include "parallel_for.h"
#include "graph.h"
#include "utility.h"

#include <stack>
#include <queue>

#define MULTIPLE_TYPEDEF MULTIPLE_TYPEDEF4

namespace
{

class StepExecutor
{
private:
    typedef BC::vertex                      vertex;
    typedef BC::IndexType                   IndexType;

    MULTIPLE_TYPEDEF(std::vector<vertex>,   VertexPredecessors,
                                            ShortestPathCounts,
                                            Distances,
                                            Dependencies);

    typedef std::vector<VertexPredecessors> VertexPredecessorsCollection;
    typedef std::stack<vertex>              ReachableVertices;

public:
    StepExecutor()
        : vpc_(res_.size())
        , spc_(res_.size(), 0)
        , d_(res_.size(), -1)
        , deps_(res_.size(), 0)
    {}

    void operator()(IndexType index)
    {
        ReachableVertices s;
        spc_[index] = 1u;
        d_[index] = 0u;

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
                    auto& distance = d_[w];
                    const auto& possibleDistance = d_[v] + 1u;
                    if (distance < 0u)
                    {
                        verticesToVisit.push(w);
                        distance = possibleDistance;
                    }
                    if (distance == possibleDistance)
                    {
                        spc_[w] += spc_[v];
                        vpc_[w].push_back(v);
                    }
            });
        }
        while (!s.empty())
        {
            const vertex w = s.top();
            s.pop();
            for (auto& v : vpc_[w])
            {
                deps_[v] += (spc_[v] / spc_[w]) * (1 + deps_[w]);
            }
            if (w != index)
            {
                res_[w] += deps_[w];
            }
        }
    }

    static void init(const graph_types::graph& g, const BC::ResultCollection& res)
    {
        g_ = g;
        res_ = res;
    }

private:
    static BC::ResultCollection res_;
    static graph_types::graph g_;

    VertexPredecessorsCollection vpc_;
    Dependencies deps_;
    ShortestPathCounts spc_;
    Distances d_;
};

BC::ResultCollection StepExecutor::res_;
graph_types::graph StepExecutor::g_;

}

BC::ResultCollection
BC::calculate(const graph_types::graph& g)
{
    const auto size = g.size();
    if (0u == size)
        return ResultCollection();

    ResultCollection res (size, 0u);
    StepExecutor::init(g, res);

    MT::parallel_for(0, size - 1, [&](IndexType index) {
        StepExecutor exec;
        exec(index);
    });
    return res;
}



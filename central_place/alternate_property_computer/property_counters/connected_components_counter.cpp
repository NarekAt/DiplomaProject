#include "connected_components_counter.h"
#include "parallel_for.h"

#include "graph.h"
#include <atomic>
#include <iostream>

ConnectedComponentsCounter::ResultCollection
ConnectedComponentsCounter::calculate(const graph_types::graph& g)
{
    std::atomic<bool> changed (true);

    if (0 == g.size())
        return ResultCollection();

    ResultCollection res (g.size(), 0);

    MT::parallel_for(0, res.size() - 1, [&](int index){
            res[index] = index; });

    while(changed)
    {
        changed = false;
        const auto edges = g.edges_sequence();
        MT::parallel_for(0, edges.size() - 1, [&](int index){
                const graph_types::vertex first = res[edges[index].first];
                const graph_types::vertex second = res[edges[index].second];
                if (first < second)
                {
                    res[second] = first;
                    changed = true;
                }
        });

        MT::parallel_for(0, res.size() - 1, [&](int index){
                auto& current = res[index];
                //while used because value can be changed in another thread
                while(current != res[current])
                {
                    current = res[current];
                }
        });
    }

    return res;
}

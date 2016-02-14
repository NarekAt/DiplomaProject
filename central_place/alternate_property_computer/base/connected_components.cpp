#include "connected_components.h"
#include "parallel_for.h"

#include "graph.h"
#include <atomic>
#include <iostream>

namespace Base
{

typedef std::lock_guard<std::mutex> Lock;

void
ConnectedComponents::computeImpl()
{
    std::atomic_bool changed (true);

    MT::parallel_for(0, results_.size() - 1, [&](unsigned index){
            results_[index] = index; });

    while(changed)
    {
        changed = false;
        const auto edges = graph_.edges_sequence();
        MT::parallel_for(0, edges.size() - 1, [&](int index){
                const graph_types::vertex first = results_[edges[index].first];
                const graph_types::vertex second = results_[edges[index].second];
                if (first < second)
                {
                    // critical section
                    {
                        Lock l(mutex_);
                        results_[second] = first;
                    }
                    changed = true;
                }
        });

        MT::parallel_for(0, results_.size() - 1, [&](int index){
                auto& current = results_[index];
                //while used because value can be changed in another thread
                while(current != results_[current])
                {
                    current = results_[current];
                }
        });
    }
}

PropertyComputerType
ConnectedComponents::typeImpl() const
{
    return CONNECTED_COMPONENTS;
}

ConnectedComponents::ResultType
ConnectedComponents::getDistributionImpl() const
{
    ResultType distributions (results_.size(), 0u);

    for (const auto& r : results_)
    {
        distributions[r]++;
    }

    return distributions;
}

} // namespace Base

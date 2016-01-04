/**
 * @file property_counters/clustering_coefficient_counter.cpp
 * @brief definition of clustering_coefficient_counter class.
 */

#include "clustering_coefficient_counter.h"
#include "utility.h"
#include "graph.h"
#include <vector>
#include "triangle_counter.h"
#include "connected_triples_counter.h"

unsigned
clustering_coefficient_counter::compute_initial_count() const
{
    const unsigned trianglesCount = triangleCounter_.compute_initial_count();
    const unsigned connTripleltsCount = connectedTriplesCounter_.compute_initial_count();

    return (3 * trianglesCount) / connTripleltsCount;
}

unsigned
clustering_coefficient_counter::compute_decrease_after_remove(const graph_types::sequent_null_edges& e) const
{
    // TODO: need to clarify
    return 0;
}

unsigned
clustering_coefficient_counter::compute_increase_after_add(const graph_types::sequent_null_edges& e) const
{
    // TODO: need to clarify
    // The same code for both: increase and decrease
    return compute_decrease_after_remove(e);
}

alternate_property_type
clustering_coefficient_counter::get_type() const
{
    return CLUSTERING_COEFFICENT;
}

clustering_coefficient_counter::clustering_coefficient_counter(graph_types::graph& graph)
    : property_counter_base(graph)
    , connectedTriplesCounter_(graph)
    , triangleCounter_(graph)
{}

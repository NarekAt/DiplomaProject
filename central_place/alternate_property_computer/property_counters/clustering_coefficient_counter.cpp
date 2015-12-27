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

unsigned clustering_coefficient_counter::compute_initial_count() const
{
    coefficient = 3*triangleCounter.compute_initial_count()/connectedTriplesCounter.compute_initial_count();
    return coefficient;
}

unsigned clustering_coefficient_counter::compute_decrease_after_remove(
                                                                  const graph_types::sequent_null_edges& e) const
{
    return 0;
}

unsigned clustering_coefficient_counter::compute_increase_after_add(
                                                               const graph_types::sequent_null_edges& e) const
{
    // The same code for both: increase and decrease :)
    return compute_decrease_after_remove(e);
}

alternate_property_type connected_triples_counter::get_type() const
{
    return CLUSTERING_COEFFICENT;
}

clustering_coefficient_counter::connected_triples_counter(
                                                     graph_types::graph& graph)
: property_counter_base(graph)
{
    connectedTriplesCounter = new connected_triples_counter(graph);
    triangleCounter = new triangle_counter(graph);
    coefficient = 0;
}

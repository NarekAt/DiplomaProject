/**
 * @file property_counters/clustering_coefficient_counter.h
 * @brief declaration of clustering_coefficient_counter class.
 */

#pragma once

#include "property_counter_base.h"
#include "connected_triples_counter.h"
#include "triangle_counter.h"

/**
 * @class clustering_coefficient_counter
 * @brief This is connected triples count computer class
 */
class clustering_coefficient_counter : public property_counter_base
{
public:
    /**
     * @brief Computes initial clustering coefficient of graph.
     */
    virtual unsigned compute_initial_count() const;
    
public:
    /**
     * @brief Gets clustering coefficient decrease value after removing edge.
     * @param e Edges to remove.
     */
    virtual unsigned compute_decrease_after_remove(
                                                   const graph_types::sequent_null_edges& e) const;
    
public:
    /**
     * @brief Gets clustering coefficient count increase value after adding edge.
     * @param e Edges to add.
     */
    virtual unsigned compute_increase_after_add(
                                                const graph_types::sequent_null_edges& e) const;
    
public:
    /**
     * @brief Gets property counter type (CLUSTERING_COEFFICENT)
     */
    virtual alternate_property_type get_type() const;
    
public:
    /**
     * @brief Constructor
     * @param graph Graph for computing clustering coefficient.
     */
    clustering_coefficient_counter(graph_types::graph& graph);
private:
    connected_triples_counter connectedTriplesCounter;
    triangle_counter triangleCounter;
    unsigned coefficient;
};
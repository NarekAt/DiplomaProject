/**
 * @file property_counters/connected_triples_counter.h
 * @brief declaration of connected_triples_counter class.
 */

#pragma once

#include "property_counter_base.h"

/**
 * @class connected_triples_counter
 * @brief This is connected triples count computer class
 */
class connected_triples_counter : public property_counter_base
{
public:
    /**
     * @brief Computes initial connected triples count of graph.
     */
    virtual unsigned compute_initial_count() const;

public:
    /**
     * @brief Gets connected triples count decrease value after removing edge.
     * @param e Edges to remove.
     */
    virtual unsigned compute_decrease_after_remove(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets connected triples count increase value after adding edge.
     * @param e Edges to add.
     */
    virtual unsigned compute_increase_after_add(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets property counter type (CONNECTED_TRIPLES_COUNT)
     */
    virtual alternate_property_type get_type() const;

public:
    /**
     * @brief Constructor
     * @param graph Graph for computing connected triples count.
     */
    connected_triples_counter(graph_types::graph& graph);
};

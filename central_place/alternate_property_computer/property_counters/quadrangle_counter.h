/**
 * @file property_counters/quadrangle_counter.h
 * @brief declaration of quadrangle_counter class.
 */

#pragma once

#include "property_counter_base.h"

/**
 * @class quadrangle_counter
 * @brief This is quadrangle count computer class
 */
class quadrangle_counter : public property_counter_base
{
public:
    /**
     * @brief Computes initial quadrangle count of graph.
     */
    virtual unsigned compute_initial_count() const;

public:
    /**
     * @brief Gets quadrangle count decrease value after removing edge.
     * @param e Edges to remove.
     */
    virtual unsigned compute_decrease_after_remove(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets quadrangle count increase value after adding edge.
     * @param e Edges to add.
     */
    virtual unsigned compute_increase_after_add(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets property counter type (quadrangle_COUNT)
     */
    virtual alternate_property_type get_type() const;

public:
    /**
     * @brief Constructor
     * @param graph Graph for computing quadrangle count.
     */
    quadrangle_counter(graph_types::graph& graph);
};

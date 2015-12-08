/**
 * @file property_counters/triangle_counter.h
 * @brief declaration of triangle_counter class.
 */

#pragma once

#include "property_counter_base.h"

/**
 * @class triangle_counter
 * @brief This is triangle count computer class
 */
class triangle_counter : public property_counter_base
{
public:
    /**
     * @brief Computes initial triangle count of graph.
     */
    virtual unsigned compute_initial_count() const;

public:
    /**
     * @brief Gets triangle count decrease value after removing edge.
     * @param e Edges to remove.
     */
    virtual unsigned compute_decrease_after_remove(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets triangle count increase value after adding edge.
     * @param e Edges to add.
     */
    virtual unsigned compute_increase_after_add(
        const graph_types::sequent_null_edges& e) const;

public:
    /**
     * @brief Gets property counter type (TRIANGLE_COUNT)
     */
    virtual alternate_property_type get_type() const;

public:
    /**
     * @brief Constructor
     * @param graph Graph for computing triangle count.
     */
    triangle_counter(graph_types::graph& graph);
};

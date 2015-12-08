/**
 * @file randomizers/fixed_degree_randomizer.h
 * @brief declaration of class fixed_degree_randomizer
 */

#pragma once

#include "randomizator_base.h"

/**
 * @class fixed_degree_randomizer
 * @brief Makes randomization by keeping degree of random
 *        selected vertices.
 */
class fixed_degree_randomizer : public randomizator_base
{
public:
    /**
     * @brief Gets step of randomizator.
     */
    virtual graph_types::remove_add_edges_pair get_step();

public:
    /**
     * @brief Gets type of randomizator (FIXED_DEGREE).
     */
    virtual randomization_type get_type() const;

public:
    /**
     * @brief Constructor
     * @param graph Graph to perform randomization.
     * @param non_existing_edges Non existing edges of graph.
     */
    fixed_degree_randomizer(graph_types::graph& graph,
        graph_types::sequent_null_edges& non_existing_edges);
};

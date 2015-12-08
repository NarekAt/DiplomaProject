/**
 * @file randomizers/random_switch_randomizer.h
 * @brief declaration of class random_switch_randomizer
 */

#pragma once

#include "randomizator_base.h"

/**
 * @class random_switch_randomizer
 * @brief Makes randomization random edge to remove and random
 *        edge to add.
 */
class random_switch_randomizer : public randomizator_base
{
public:
    /**
     * @brief Gets step of randomizator.
     */
    virtual graph_types::remove_add_edges_pair get_step();

public:
    /**
     * @brief Gets type of randomizator (RANDOM_SWITCH).
     */
    virtual randomization_type get_type() const;

public:
    /**
     * @brief Constructor
     * @param graph Graph to perform randomization.
     * @param non_existing_edges Non existing edges of graph.
     */
    random_switch_randomizer(graph_types::graph& graph,
        graph_types::sequent_null_edges& non_existing_edges);
};

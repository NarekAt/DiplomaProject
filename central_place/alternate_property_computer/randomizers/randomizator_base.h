/**
 * @file randomizers/randomizator_base.h 
 * @brief declaration of class randomizator_base
 */

#pragma once

#include "types.h"
#include "graph_types.h"

namespace graph_types {
    class graph;
}

/**
 * @class randomizator_base
 * @brief class for performing randomization step.
 */
class randomizator_base
{
public:
    /**
     * @brief Gets step of randomizator.
     */
    virtual graph_types::remove_add_edges_pair get_step() = 0;

public:
    /**
     * @brief Gets type of randomizator.
     */
    virtual randomization_type get_type() const = 0;

public:
    /**
     * @brief Constructor
     * @param graph Graph to perform randomization.
     * @param non_existing_edges Non existing edges of graph.
     */
    randomizator_base(graph_types::graph& graph,
        graph_types::sequent_null_edges& non_existing_edges);

protected:
    graph_types::random_generator m_random_generator;
    graph_types::graph& m_graph;
    graph_types::sequent_null_edges& m_non_existing_edges;
};

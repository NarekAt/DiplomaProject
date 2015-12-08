/**
 * @file randomizers/randomizator_factory.h 
 * @brief declaration of randomizator_factory class
 */

#pragma once

#include "types.h"
#include "graph_types.h"

class randomizator_base;

namespace graph_types {
    class graph;
}

/**
 * @class randomizator_factory
 * @brief creater of randomizators.
 */
class randomizator_factory
{
public:
    /**
     * @brief Creates and gets randomizator
     *        by given randomization_type.
     * @param graph Graph for randomizator.
     * @param non_existing_edges Non existing edges of graph.
     * @param t Randomization type.
     * @note Got pointer must be deleted after use.
     */
    static randomizator_base* get_randomizator(graph_types::graph& graph, 
        graph_types::sequent_null_edges& non_existing_edges, randomization_type t);
};

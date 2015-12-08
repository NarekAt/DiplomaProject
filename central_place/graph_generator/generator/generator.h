#pragma once

/**
 * @file generator/generator.h
 * @brief declaration of generator class.
 */

#include "graph.h"
#include <fstream>

/**
 * @class generator
 * @brief Generates graph.
 */
class generator
{
public:
    /**
     * @brief Runs graph generator.
     * @param n size of graph.
     * @param p probability of edge in graph.
     * @param t core data type of graph.
     */
    graph_types::graph run(const graph_types::graph_size s, const double p,
        const graph_types::storage_core_type t, std::ofstream& logger) const;
};

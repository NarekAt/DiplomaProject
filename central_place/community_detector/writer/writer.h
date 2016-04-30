#pragma once

/**
 * @file writer/writer.h 
 * @brief declaration of writer class.
 */

#include "graph_types.h"
#include <string>
#include <fstream>

namespace graph_types {
    class graph;
}

/**
 * @class writer
 * @brief writes graph.
 */
class writer
{
public:
    /**
     * @brief Runs graph writer.
     * @param g Graph to write
     * @param n size of graph.
     * @param p probability of edge in graph.
     * @param f output file name.
     */
    void run(const graph_types::graph& g, const graph_types::graph_size s,
        const double p, const std::string& f, std::ofstream& logger) const;
};

/**
 * @file common/utility.h
 * @brief declarations of utility functions
 */

#pragma once

#include "graph_types.h"

namespace utility
{

/**
 * @brief Returns another vertex of the edge.
 * @param v Initial vertex
 * @param e Edge
 * @return Another vertex of v
 * @pre vertex must be one of the vertices of given edge
 */
graph_types::vertex get_another_vertex(graph_types::vertex v, graph_types::edge e);

}

/**
 * @file common/utility.h
 * @brief declarations of utility functions
 */

#pragma once

#include "graph_types.h"

#define MULTIPLE_TYPEDEF2(type, n1, n2) \
    typedef type n1;                    \
    typedef type n2

#define MULTIPLE_TYPEDEF3(type, n1, n2, n3) \
    MULTIPLE_TYPEDEF2(type, n1, n2);        \
    typedef type n3

#define MULTIPLE_TYPEDEF4(type, n1, n2, n3, n4) \
    MULTIPLE_TYPEDEF3(type, n1, n2, n3);        \
    typedef type n4


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

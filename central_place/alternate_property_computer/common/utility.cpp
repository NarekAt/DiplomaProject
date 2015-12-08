/**
 * @file common/utility.cpp
 * @brief definitions of utility functions
 */

#include "utility.h"
#include <assert.h>

namespace utility
{

graph_types::vertex get_another_vertex(graph_types::vertex v, graph_types::edge e)
{
    graph_types::vertex s = e.first;
    graph_types::vertex t = e.second;
    if (v == s) {
        return t;
    }
    assert(v == t);
    return s;
}

}

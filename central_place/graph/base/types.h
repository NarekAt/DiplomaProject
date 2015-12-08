#pragma once

/**
 * @file base/types.h
 * @brief declaration basic graph types.
 */

#include "three_byte_vertex.h"
#include <set>
#include <vector>
#include <random>

namespace graph_types
{

typedef three_byte_vertex vertex;
typedef vertex graph_size;
typedef std::set<vertex> set_of_vertices;
typedef std::vector<vertex> sequence_of_vertices;
typedef std::pair<vertex, vertex> edge;
typedef std::set<edge> set_of_edges;
typedef std::vector<edge> sequence_of_edges;
typedef std::mt19937 random_generator;

enum class storage_core_type : unsigned {
    BITSETS_FULL,
    BITSETS_PARTIAL,
    SORTED_VECTORS_FULL,
    SORTED_VECTORS_PARTIAL,
    AUTODETECT,
    INVALID_CT
};

/**
 * @brief Gets core type value by name.
 * @param t_n Core type name.
 * @return Returns appropriate core type 
 *         if it is valid, otherwise returns INVALID_CT enum value.
 */
storage_core_type get_core_type_by_name(
    const std::string& t_n);
}

/**
 * @file graph_types/graph_types.cpp
 * @brief definitions of functions which works with graph types.
 */

#include "graph_types.h"
#include <map>
#include <assert.h>

namespace graph_types
{

std::map<std::string, storage_core_type> s_ctname_to_rtype {
    std::make_pair("bitsets_full", storage_core_type::BITSETS_FULL),
    std::make_pair("bitsets_partial", storage_core_type::BITSETS_PARTIAL),
    std::make_pair("sorted_vectors_full", storage_core_type::SORTED_VECTORS_FULL),
    std::make_pair("sorted_vectors_partial", storage_core_type::SORTED_VECTORS_PARTIAL),
    std::make_pair("autodetect", storage_core_type::AUTODETECT)
};

storage_core_type get_core_type_by_name(
    const std::string& t_n)
{
    auto ct_it = s_ctname_to_rtype.find(t_n);
    if (s_ctname_to_rtype.end() != ct_it) {
        return ct_it->second;
    }
    return storage_core_type::INVALID_CT;
}

vertex invalidVertex()
{
    return std::numeric_limits<unsigned>::max();
}

edge invalidEdge()
{
    return edge(invalidVertex(), invalidVertex());

}

}

/**
 * @file common/types.cpp
 * @brief definitions of functions which works with common types.
 */

#include "types.h"
#include <assert.h>

bool is_graph_item_related_property(const alternate_property_type t)
{
    return t > 3 && t != 9;
}

std::map<std::string, randomization_type> s_rname_to_rtype {
    std::make_pair("fixed_degree", randomization_type::FIXED_DEGREE),
    std::make_pair("random_switch", randomization_type::RANDOM_SWITCH)
};

randomization_type get_randomization_type_by_name(
    const std::string& t_n)
{
    auto r_it = s_rname_to_rtype.find(t_n);
    if (s_rname_to_rtype.end() != r_it) {
        return r_it->second;
    }
    return randomization_type::INVALID_RT;
}

std::map<randomization_type, std::string> s_rtype_to_rname {
    std::make_pair(randomization_type::FIXED_DEGREE, "fixed degree"),
    std::make_pair(randomization_type::RANDOM_SWITCH, "random switch"),
};

std::string get_randomization_name_by_type(
    randomization_type t)
{
    auto r_it = s_rtype_to_rname.find(t);
    assert(s_rtype_to_rname.end() != r_it);
    return r_it->second;
}

std::map<std::string, alternate_property_type> s_apname_to_aptype {
    std::make_pair("triangle_count",
        alternate_property_type::TRIANGLE_COUNT),
    std::make_pair("quadrangle_count",
        alternate_property_type::QUADRANGLE_COUNT),
    std::make_pair("connected_triples_count",
        alternate_property_type::CONNECTED_TRIPLES_COUNT),
    std::make_pair("clustering_coefficent",
        alternate_property_type::CLUSTERING_COEFFICENT),
    std::make_pair("connected_components",
        alternate_property_type::CONNECTED_COMPONENTS),
    std::make_pair("shortest_path",
        alternate_property_type::SHORTEST_PATH),
    std::make_pair("betweenness_centrality",
        alternate_property_type::BETWEENNESS_CENTRALITY),
    std::make_pair("eigenvector_centrality",
        alternate_property_type::EIGENVECTOR_CENTRALITY),
    std::make_pair("eigen_values",
        alternate_property_type::EIGEN_VALUES),
    std::make_pair("degree",
        alternate_property_type::DEGREE)
};

alternate_property_type get_alternate_property_type_by_name(
    const std::string& t_n)
{
    auto ap_it = s_apname_to_aptype.find(t_n);
    if (s_apname_to_aptype.end() != ap_it) {
        return ap_it->second;
    }
    return alternate_property_type::INVALID_APT;
}

std::map<alternate_property_type, std::string> s_aptype_to_apname {
    std::make_pair(alternate_property_type::TRIANGLE_COUNT,
            "triangle count"),
    std::make_pair(alternate_property_type::QUADRANGLE_COUNT,
            "quadrangle count"),
    std::make_pair(alternate_property_type::CONNECTED_TRIPLES_COUNT,
            "connected_triples_count"),
    std::make_pair(alternate_property_type::CLUSTERING_COEFFICENT,
            "clustering_coefficent"),
    std::make_pair(alternate_property_type::CONNECTED_COMPONENTS,
            "connected_components"),
    std::make_pair(alternate_property_type::SHORTEST_PATH,
            "shortest_path"),
    std::make_pair(alternate_property_type::BETWEENNESS_CENTRALITY,
            "betweenness_centrality"),
    std::make_pair(alternate_property_type::EIGENVECTOR_CENTRALITY,
            "eigenvector_centrality"),
    std::make_pair(alternate_property_type::EIGEN_VALUES,
            "eigen_values"),
    std::make_pair(alternate_property_type::DEGREE,
            "degree")
};

std::string get_alternate_property_name_by_type(
    alternate_property_type t)
{
    auto ap_it = s_aptype_to_apname.find(t);
    assert(s_aptype_to_apname.end() != ap_it);
    return ap_it->second;
}

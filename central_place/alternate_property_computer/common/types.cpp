/**
 * @file common/types.cpp
 * @brief definitions of functions which works with common types.
 */

#include "types.h"
#include <assert.h>

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
        alternate_property_type::CLUSTERING_COEFFICENT)
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

std::map<std::string, PropertyComputerType> s_giname_to_gitype {
    std::make_pair("connected_components",
        PropertyComputerType::CONNECTED_COMPONENTS),
    std::make_pair("shortest_path",
        PropertyComputerType::SHORTEST_PATH),
    std::make_pair("betweenness_centrality",
        PropertyComputerType::BETWEENNESS_CENTRALITY),
    std::make_pair("eigen_values",
        PropertyComputerType::EIGEN_VALUES),
    std::make_pair("degree",
        PropertyComputerType::DEGREE)
};

PropertyComputerType get_graph_item_property_type_by_name(
    const std::string& t_n)
{
    auto gi_it = s_giname_to_gitype.find(t_n);

    if (s_giname_to_gitype.end() != gi_it) {
        return gi_it->second;
    }
    return  PropertyComputerType::INVALID_PCT;
}

std::map<alternate_property_type, std::string> s_aptype_to_apname {
    std::make_pair(alternate_property_type::TRIANGLE_COUNT,
            "triangle count"),
    std::make_pair(alternate_property_type::QUADRANGLE_COUNT,
            "quadrangle count"),
    std::make_pair(alternate_property_type::CONNECTED_TRIPLES_COUNT,
            "connected_triples_count"),
    std::make_pair(alternate_property_type::CLUSTERING_COEFFICENT,
            "clustering_coefficent")
};

std::string get_alternate_property_name_by_type(
    alternate_property_type t)
{
    auto ap_it = s_aptype_to_apname.find(t);
    assert(s_aptype_to_apname.end() != ap_it);
    return ap_it->second;
}

std::map<PropertyComputerType, std::string> s_gritype_to_griname {
    std::make_pair(PropertyComputerType::CONNECTED_COMPONENTS,
            "connected_components"),
    std::make_pair(PropertyComputerType::SHORTEST_PATH,
            "shortest_path"),
    std::make_pair(PropertyComputerType::BETWEENNESS_CENTRALITY,
            "betweenness_centrality"),
    std::make_pair(PropertyComputerType::EIGEN_VALUES,
            "eigen_values"),
    std::make_pair(PropertyComputerType::DEGREE,
            "degree")
};

std::string get_graph_item_property_name_by_type(
    PropertyComputerType t)
{
    auto sp_it = s_gritype_to_griname.find(t);
    assert(s_gritype_to_griname.end() != sp_it);
    return sp_it->second;
}

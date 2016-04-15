/**
 * @file common/types.h
 * @brief common typedefs enums e.t.c
 */

#pragma once

#include <map>
#include <set>
#include <list>
#include <string>
#include <boost/any.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>

/**
 * @brief Map of process arguments name to value.
 */
typedef std::map<std::string, boost::any> arg_name_to_value_map;

/**
 * @enum randomization_type
 * @brief This type shows how to randomize graphs.
 * @note INVALID_RT value notifies that
 *       invalid name of type was red.
 */
enum randomization_type {
    RANDOM_SWITCH,
    FIXED_DEGREE,
    INVALID_RT
};

/**
 * @brief Gets randomization type value by name.
 * @param t_n Randomization type name.
 * @return Returns appropriate randomization type
 *         if it is valid, otherwise returns INVALID_RT enum value.
 */
randomization_type get_randomization_type_by_name(
    const std::string& t_n);

/**
 * @brief Gets randomization type name by value.
 * @param t Randomization type.
 */
std::string get_randomization_name_by_type(
    randomization_type t);

/**
 * @enum alternate_property_type
 * @brief This type shows what property to compute from graphs.
 * @note INVALID_APT value notifies that
 *       invalid name of type was red.
 */
enum alternate_property_type {
    TRIANGLE_COUNT = 0,
    QUADRANGLE_COUNT,
    CONNECTED_TRIPLES_COUNT,
    CLUSTERING_COEFFICENT,
    CONNECTED_COMPONENTS,
    SHORTEST_PATH,
    BETWEENNESS_CENTRALITY,
    EIGENVECTOR_CENTRALITY,
    EIGEN_VALUES,
    DEGREE,
    INVALID_APT
};

typedef std::vector<alternate_property_type> apt_list;

bool is_graph_item_related_property(const alternate_property_type t);

/**
 * @brief Gets alternate property type value by name.
 * @param t_n Alternate property type name.
 * @return Returns appropriate alternate property type
 *         if it is valid, otherwise returns INVALID_APT enum value.
 */
alternate_property_type get_alternate_property_type_by_name(
    const std::string& t_n);

/**
 * @brief Gets alternate property type name by value.
 * @param t Aternate property type.
 */
std::string get_alternate_property_name_by_type(
    alternate_property_type t);

static int s_status_step = 500;

/**
 * @brief Persent of work which was done to mu
 */
typedef std::pair<double, double> persent_to_mu;

/**
 * @brief mu values list.
 */
typedef std::vector<double> mu_list;

/**
 * @brief process id to mu count map.
 */
typedef std::vector<std::pair<unsigned, unsigned>> process_to_mu_count;

/**
 * @brief mpi tag to mu vector.
 */
typedef std::vector<std::pair<unsigned, double>> tag_to_mu_map;

/**
 * @brief Work status tags for process.
 */
typedef std::vector<unsigned> status_tags;

/**
 * @brief Process to status tags.
 */
typedef std::map<unsigned, status_tags> process_to_status_tags;
/**
 * @brief vector of pairs: step number to setp property count.
 */
typedef std::vector<std::pair<unsigned, double>> single_results_list;

/**
 * @brief map from mu value to appropriate vector of pairs:
 *        step number to step property count.
 */
typedef std::vector<std::pair<double, single_results_list>>
    calculation_results;



#pragma once

/**
 * @file io/erdos_renyi_reader.h
 * @brief declaration of erdos_renyi_reader class
 */

/**
 * TODO: 
 *      1) make base class for readers
 *      2) mu file reader is the same for any graph readers,
 *         so it must be migrated to the base class.
 */

#include "types.h"

namespace graph_types
{
    class graph;
}

/**
 * @class erdos_renyi_reader
 * @brief This class is for reading erdos renyi graphs
 *        and mu files.
 */
class erdos_renyi_reader
{
public:
    /**
     * @brief Reads mu values from file.
     * @param f_n mu values file name.
     * @param[out] mus container of mu values.
     */
    void get_mus_from_file(const std::string& f_n,
        mu_list& mus) const;

public:
    /**
     * @brief Reads graph and properties from file.
     * @param f_n graph file name.
     * @param[out] graph graph object to be red.
     * @param[out] v_c Vertex count to be red.
     * @param[out] p Probability to be red.
     */
    void get_graph_and_properties_from_file(const std::string& f_n,
        graph_types::graph& graph, unsigned& v_c, double& p);
};

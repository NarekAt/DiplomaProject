/**
 * @file io/erdos_renyi_reader.cpp
 * @brief definition of erdos_renyi_reader class
 */

#include "erdos_renyi_reader.h"
#include "graph.h"
#include <fstream>
#include <boost/archive/text_iarchive.hpp>


void erdos_renyi_reader::get_mus_from_file(const std::string& f_n,
    mu_list& mus) const
{
    std::ifstream mu_file;
    mu_file.open(f_n);
    if (!mu_file.is_open()) {
        // TODO: throw exception.
    }
    double mu = 0.0;
    while (mu_file >> mu) {
        mus.push_back(mu);
    }
    mu_file.close();
}

#include <iostream>
void erdos_renyi_reader::get_graph_and_properties_from_file(
    const std::string& f_n, graph_types::graph& graph,
    unsigned& v_c, double& p)
{
    std::ifstream graph_file;
    graph_file.open(f_n, std::fstream::in);
    if (!graph_file.is_open()) {
        // TODO: throw exception.
    }

    boost::archive::text_iarchive ia(graph_file);
    ia >> v_c >> p >> graph;

    graph_file.close();
}

/**
 * @file writer/writer.cpp
 * @brief definition of writer class.
 */

#include "writer.h"
#include "graph.h"
#include <boost/archive/text_oarchive.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

void writer::run(const graph_types::graph& g, const graph_types::graph_size s,
    const double p, const std::string& f, std::ofstream& logger) const
{
    time_t c_t = time(0);
    logger << "\n>>>>> Graph writing Started: " << ctime(&c_t);
    std::ofstream graph_file;
    graph_file.open(f);
    if (!graph_file.is_open()) {
        // TODO: throw exception.
        return;
    }
    boost::archive::text_oarchive oa(graph_file);
    oa << s << p << g;
    graph_file.close();
    c_t = time(0);
    logger << "\n>>>>> Graph writing Finished: " << ctime(&c_t);
}

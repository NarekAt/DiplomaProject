
#pragma once

#include "graph.h"
#include "types.h"

#include <fstream>

class igraph_task_manager
{
public:
    igraph_task_manager(const graph_types::graph& g,
                        const alternate_property_type apt,
                        std::ofstream& logger)
        : m_initial_graph(g)
        , m_alternate_property_type(apt)
        , m_logger(logger)
    {}

    virtual void run() = 0;

protected:
    graph_types::graph      m_initial_graph;
    alternate_property_type m_alternate_property_type;

    std::ofstream&          m_logger;
};

#include "connected_components_counter.h"
#include "graph.h"

#include <ctime>
#include <chrono>

#include "gtest/gtest.h"

using namespace graph_types;

namespace
{

TEST(ConnectedComponentsTest, xxx)
{
    graph g(graph_size(20), storage_core_type::BITSETS_FULL);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(4, 5);
    g.add_edge(6, 7);
    g.add_edge(7, 8);
    g.add_edge(9, 10);
    g.add_edge(10, 11);
    g.add_edge(11, 12);
    g.add_edge(13, 14);
    g.add_edge(15, 17);
    g.add_edge(17, 18);
    g.add_edge(0, 16);
    g.add_edge(16, 19);

    ConnectedComponentsCounter::ResultCollection res = ConnectedComponentsCounter::calculate(g);

    for (auto& r : res)
    {
        std::cout << r << std::endl;
    }
}

}


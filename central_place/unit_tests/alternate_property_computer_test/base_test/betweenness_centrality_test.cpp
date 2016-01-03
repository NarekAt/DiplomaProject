#include "betweenness_centrality.h"
#include "graph.h"

#include <gtest/gtest.h>
#include <iostream>

namespace
{

using namespace graph_types;
using namespace Base;

/*TEST(BetweennessCentralityTest, xxx)
{
    graph g (graph_size(5), storage_core_type::BITSETS_FULL);

    BC::ResultCollection res = BC::calculate(g);

    for (auto& i : res)
        EXPECT_EQ(i, 0u);
}*/

TEST(BetweennessCentralityTest, yyy)
{
    graph g(graph_size(6), storage_core_type::BITSETS_FULL);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 5);
    g.add_edge(2, 4);

    BC b (g);
    b.compute();
    BC::ResultType res = b.getResult();
    for (auto& i : res)
        std::cout << i << std::endl;
}

}

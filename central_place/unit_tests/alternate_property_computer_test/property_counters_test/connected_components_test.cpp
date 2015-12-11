#include "connected_components_counter.h"
#include "graph.h"

#include <ctime>
#include <chrono>

#include "gtest/gtest.h"

using namespace graph_types;

namespace
{

TEST(ConnectedComponentsCounter, ShouldReturnItselfsForDisconnectedVertices)
{
    graph g(graph_size(5), storage_core_type::BITSETS_FULL);

    ConnectedComponentsCounter::ResultCollection res = ConnectedComponentsCounter::calculate(g);
    ASSERT_EQ(res.size(), 5u);

    for (size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(res[i], i);
    }
}

TEST(ConnectedComponentsTest, ShouldTestOnGraphWithExactlyOneConnectedComponnent)
{
    graph g(graph_size(6), storage_core_type::BITSETS_FULL);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(4, 5);

    ConnectedComponentsCounter::ResultCollection res = ConnectedComponentsCounter::calculate(g);

    for (const auto& i : res)
    {
        EXPECT_EQ(i, 0);
    }
}

TEST(ConnectedComponentsTest, ShouldCheckCaseWithConnectedBlockOfVerticesAndWithOneDisconnectedVertex)
{
    graph g(graph_size(7), storage_core_type::BITSETS_FULL);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(4, 5);

    ConnectedComponentsCounter::ResultCollection res = ConnectedComponentsCounter::calculate(g);

    for (size_t i = 0; i < 6; ++i)
    {
        EXPECT_EQ(res[i], 0);
    }

    EXPECT_EQ(res[6], 6);
}

TEST(ConnectedComponentsTest, ShouldCheckOnMultiComponentGraph)
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

    ConnectedComponentsCounter::ResultCollection res = ConnectedComponentsCounter::calculate(g);

    // Component 1
    for (size_t i = 1; i <= 5; ++i)
        EXPECT_EQ(res[i], 1);
    // Component 6
    for (size_t i = 6; i <= 8; ++i)
        EXPECT_EQ(res[i], 6);
    // Component 9
    for (size_t i = 9; i <= 12; ++i)
        EXPECT_EQ(res[i], 9);
    // Component 13
    for (size_t i = 13; i <=14; ++i)
        EXPECT_EQ(res[i], 13);
    // Component 15
        EXPECT_EQ(res[15], 15);
        EXPECT_EQ(res[17], 15);
        EXPECT_EQ(res[18], 15);

    // Disconnected Components
        EXPECT_EQ(res[0], 0);
        EXPECT_EQ(res[16], 16);
        EXPECT_EQ(res[19], 19);

    for (auto& r : res)
    {
        std::cout << r << std::endl;
    }
}

}


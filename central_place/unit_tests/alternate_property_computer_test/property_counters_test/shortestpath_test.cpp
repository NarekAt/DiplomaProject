#include "shortestpath.hpp"
#include <ctime>
#include <chrono>

#include "gtest/gtest.h"

using namespace graph_types;

namespace
{

TEST(ShortestPathTest, ShouldReturnEmptyResultForGraphWihtoutAnyEdges)
{
    graph g (graph_size(110), storage_core_type::BITSETS_FULL);

    sequence_of_vertices vertices;

    ShortestPath::PathLengthProp lengths;
    ShortestPath::calculate(g, vertices, lengths);

    EXPECT_EQ(lengths.size(), 0u);

    vertices.push_back(vertex(3));

    EXPECT_EQ(lengths.size(), 0u);
}

TEST(ShortestPathTest, PathForTerminalVertexShouldBeZero)
{
    graph g (graph_size(10), storage_core_type::BITSETS_FULL);

    g.add_edge(2, 5);

    sequence_of_vertices vertices (1, vertex(5));
    ShortestPath::PathLengthProp lengths;
    ShortestPath::calculate(g, vertices, lengths);

    ASSERT_EQ(lengths.size(), 2u);

    EXPECT_EQ(lengths[vertex(5)], 0);
}

TEST(ShortestPathTest, ShouldCalculatePathsForNonEmptyGraphWithTwoSources)
{
    graph g (graph_size(100), storage_core_type::BITSETS_FULL);

    g.add_edge(1, 4);
    g.add_edge(2, 6);
    g.add_edge(3, 10);
    g.add_edge(5, 8);
    g.add_edge(2, 39);
    g.add_edge(10, 34);
    g.add_edge(4, 55);
    g.add_edge(29, 33);
    g.add_edge(21, 44);
    g.add_edge(23, 66);
    g.add_edge(66, 88);
    g.add_edge(88, 55);
    g.add_edge(66, 55);

    sequence_of_vertices vertices;
    vertices.push_back(vertex(2));
    vertices.push_back(vertex(4));

    ShortestPath::PathLengthProp lengths;

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << ">>>> Calculation Started: " << std::endl;

    ShortestPath::calculate(g, vertices, lengths);

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << ">>>> Calculation Finished: " << microseconds << " microseconds." << std::endl;

    EXPECT_EQ(lengths[vertex(1)], 1);
    EXPECT_EQ(lengths[vertex(2)], 0);
    EXPECT_EQ(lengths[vertex(4)], 0);
    EXPECT_EQ(lengths[vertex(6)], 1);
    EXPECT_EQ(lengths[vertex(23)], 3);
    EXPECT_EQ(lengths[vertex(39)], 1);
    EXPECT_EQ(lengths[vertex(55)], 1);
}

}

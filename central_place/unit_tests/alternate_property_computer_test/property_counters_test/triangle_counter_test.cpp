#include "triangle_counter.h"
#include "graph.h"
#include <gtest/gtest.h>

using namespace graph_types;

namespace
{

TEST(TriangleCounterTest, ShouldComputeInitialCountForEmptyGraph)
{
    graph g(graph_size(1200), storage_core_type::BITSETS_FULL);

    triangle_counter counter (g);
    EXPECT_EQ(counter.compute_initial_count(), 0);
}

TEST(TriangleCounterTest, ShouldComputeInitialCountForNonEmptyGraph)
{
    graph g(graph_size(1200), storage_core_type::BITSETS_FULL);

    g.add_edge(2, 4);
    g.add_edge(4, 5);
    g.add_edge(2, 5);
    g.add_edge(44, 89);
    g.add_edge(89, 100);
    g.add_edge(44, 100);
    g.add_edge(2, 199);

    triangle_counter counter (g);
    EXPECT_EQ(counter.compute_initial_count(), 2);

    graph g2(graph_size(100), storage_core_type::BITSETS_FULL);
    g2.add_edge(3, 4);
    g2.add_edge(8, 11);
    g2.add_edge(4, 8);

    triangle_counter counter2 (g2);
    EXPECT_EQ(counter2.compute_initial_count(), 0);
}

TEST(TriangleCounterTest, ShouldComputeAndDecreaseAfterRemove)
{
    graph g(graph_size(1000), storage_core_type::BITSETS_FULL);

    g.add_edge(2, 4);
    g.add_edge(4, 5);
    g.add_edge(2, 5);
    g.add_edge(44, 89);
    g.add_edge(89, 100);
    g.add_edge(44, 100);
    g.add_edge(2, 199);

    triangle_counter counter (g);
    sequent_null_edges seq;
    seq.push_back(edge(2, 5));
    const unsigned count = counter.compute_decrease_after_remove(seq);

    EXPECT_EQ(count, 1);
}

TEST(TriangleCounterTest, ShouldComputeAndIncreaseAfterAdding)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);
    g.add_edge(1, 30);
    g.add_edge(30, 10);
    g.add_edge(1, 10);

    triangle_counter counter(g);
    unsigned count = counter.compute_initial_count();
    ASSERT_EQ(count, 1);

    sequent_null_edges seq;
    seq.push_back(edge(1, 10));

    count = counter.compute_increase_after_add(seq);
    EXPECT_EQ(count, 1);
}

} // unnamed namespace
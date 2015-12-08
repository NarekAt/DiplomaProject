#include "quadrangle_counter.h"
#include "graph.h"

#include "gtest/gtest.h"

using namespace graph_types;

TEST(QuadrangleCounterTest, ShouldComputeInitialCountForEmptyGraph)
{
    graph g (graph_size(1100), storage_core_type::BITSETS_FULL);

    quadrangle_counter counter (g);
    EXPECT_EQ(counter.compute_initial_count(), 0);
}

TEST(QuadrangleCounterTest, ShouldComputeInitialCountForNonEmptyGraph)
{

}

TEST(QuadrangleCounterTest, ShouldComputeAndDecreaseAfterRemove)
{

}

TEST(QuadrangleCounterTest, ShouldComputeAndIncreaseAfterAdd)
{

}

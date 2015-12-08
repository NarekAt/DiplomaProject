#include "random_switch_randomizer.h"
#include "graph.h"
#include <iostream>

#include <gtest/gtest.h>

using namespace graph_types;

TEST(RandomSwitchRandomizerTest, ShouldConstuctRandomizerAndGetType)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);
    g.add_edge(4, 5);
    g.add_edge(18, 20);

    sequent_null_edges edges;
    edges.push_back(edge(11, 10));
    edges.push_back(edge(88, 98));

    random_switch_randomizer randomizer (g, edges);

    EXPECT_TRUE(randomizer.get_type() == RANDOM_SWITCH);
}

TEST(RandomSwitchRandomizerTest, ShouldCheckStepCollectionSize)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);

    g.add_edge(3, 5);
    g.add_edge(18, 20);
    g.add_edge(11, 22);
    g.add_edge(45, 66);

    sequent_null_edges e;
    e.push_back(edge(18, 45));

    random_switch_randomizer r (g, e);

    auto step = r.get_step();
    EXPECT_EQ(step.first.size(), 1);
    EXPECT_EQ(step.second.size(), 1);
}

TEST(RandomSwitchRandomizerTest, ShouldThrowAssetionFailureWhenPassedAnExistingEdge)
{
    graph g(graph_size(10), storage_core_type::BITSETS_FULL);

    g.add_edge(4, 5);
    g.add_edge(3, 6);

    sequent_null_edges e;
    e.push_back(edge(3, 6));

    random_switch_randomizer r (g, e);
    ASSERT_DEATH({r.get_step();},"");
}

TEST(RandomSwitchRandomizerTest, ShouldCheckGetStepResultedCollection)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);

    g.add_edge(10, 45);
    g.add_edge(88, 22);
    g.add_edge(23, 44);
    g.add_edge(88, 97);

    sequent_null_edges e;
    e.push_back(edge(3, 4));
    e.push_back(edge(5, 10));

    random_switch_randomizer r(g, e);
    auto step = r.get_step();

    EXPECT_TRUE(g.edge_exists(step.first[0]));

    const edge nonExistingEdge = step.second[0];
    EXPECT_FALSE(g.edge_exists(nonExistingEdge));

    const auto it = std::find(e.begin(), e.end(), nonExistingEdge);
    EXPECT_TRUE(it == e.end());
}


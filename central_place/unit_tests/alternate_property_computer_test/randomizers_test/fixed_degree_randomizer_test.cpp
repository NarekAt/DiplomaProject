#include "fixed_degree_randomizer.h"
#include "graph.h"
#include <iostream>

#include <gtest/gtest.h>

using namespace graph_types;

namespace
{

bool checkEdgesCollection(const sequent_null_edges& edges, const edge& e)
{
    return std::find(edges.begin(), edges.end(), e) != edges.end();
}

}

TEST(FixedDegreeRandomizerTest, ShouldConstuctRandomizerAndGetType)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);
    g.add_edge(3, 5);
    g.add_edge(18, 20);

    sequent_null_edges edges;
    edges.push_back(edge(3, 10));
    edges.push_back(edge(88, 98));

    fixed_degree_randomizer randomizer (g, edges);

    EXPECT_TRUE(randomizer.get_type() == FIXED_DEGREE);
}

TEST(FixedDegreeRandomizerTest, ShouldCheckStepCountCollectionSize)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);

    g.add_edge(3, 5);
    g.add_edge(18, 20);

    sequent_null_edges e;
    fixed_degree_randomizer r (g, e);

    auto step = r.get_step();
    EXPECT_EQ(step.first.size(), 2);
    EXPECT_EQ(step.second.size(), 2);
}

TEST(FixedDegreeRandomizerTest, ShouldCheckEdgesExistanceInGetStepResultColl)
{
    graph g(graph_size(100), storage_core_type::BITSETS_FULL);

    g.add_edge(3, 5);
    g.add_edge(18, 20);
    g.add_edge(29, 18);
    g.add_edge(21, 5);
    g.add_edge(33, 44);

    sequent_null_edges edges;
    fixed_degree_randomizer randomizer (g, edges);

    auto step = randomizer.get_step();

    ASSERT_TRUE(step.first.size() == step.second.size());

    const edge e1 = step.first[0];
    const edge e2 = step.first[1];

    const vertex vs1 = e1.first;
    const vertex vt1 = e1.second;
    const vertex vs2 = e2.first;
    const vertex vt2 = e2.second;

    const bool ok = (e1 != e2 && vs1 != vs2 && vt1 != vt2 &&
                    vs1 != vt2 && vt1 != vs2 &&
                    !g.edge_exists(vs1, vs2) &&
                    !g.edge_exists(vs1, vt2) &&
                    !g.edge_exists(vt1, vt2) &&
                    !g.edge_exists(vt1, vs2));

    EXPECT_TRUE(ok);
}

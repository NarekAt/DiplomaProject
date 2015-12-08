//////////////////////////////////////////////////////////
//     Description:                                     //
//          To run and test graph basic operations.     //
//          The steps are followings:                   //
//          - Cover Graph readonly interfaces.          //
//          - Cover Graph modifiable interface.         //
//                                                      //
//                                                      //
//////////////////////////////////////////////////////////


#include <algorithm>
#include "graph.h"

#include <gtest/gtest.h>

namespace
{

using namespace graph_types;

class GraphTest : public testing::Test
{
protected:
    // will be called at the beginning of every GraphTest test.
    virtual void SetUp()
    {
        g_ = graph(graph_size(1200), storage_core_type::BITSETS_FULL);
    }

public:
    void update(const graph_size size, storage_core_type type)
    {
        g_ = graph(size, type);
    }

    void initNeighborsCollectionTest(const vertex v1)
    {
        const vertex v2 (2);
        const vertex v3 (3);
        const vertex v4 (4);
        const vertex v5 (5);
        const vertex v6 (6);

        g_.add_edge(v1, v2);
        g_.add_edge(v3, v4);
        g_.add_edge(v1, v3);
        g_.add_edge(v3, v5);
        g_.add_edge(v4, v6);
    }
    graph_types::graph g_;
};

TEST_F(GraphTest, ShouldCheckConstructedGraphSize)
{
    EXPECT_EQ(g_.size(), three_byte_vertex(1200));
}

TEST_F(GraphTest, IsEdgeExistsFor2Vertices)
{
    const vertex v1 (2);
    const vertex v2 (3);
    g_.add_edge(v1, v2);

    EXPECT_TRUE(g_.edge_exists(v1, v2));
}

TEST_F(GraphTest, IsEdgeExistsForEdge)
{
    const edge e = std::make_pair(vertex(4), vertex(18));
    g_.add_edge(e);
    EXPECT_TRUE(g_.edge_exists(e));
}

TEST_F(GraphTest, AddEdgeNegativeCase)
{
    const edge e(2, 4);
    g_.add_edge(e);

    ASSERT_DEATH({g_.add_edge(e);},"");
}

TEST_F(GraphTest, RemoveEdge)
{
    const vertex v1 (2);
    const vertex v2 (3);
    g_.add_edge(v1, v2);

    ASSERT_TRUE(g_.edge_exists(v1, v2));

    g_.remove_edge(v1, v2);
    EXPECT_FALSE(g_.edge_exists(v1, v2));
}

TEST_F(GraphTest, RemoveEdgeNegativeCase)
{
    const edge e (3, 5);
    const edge e2 (4, 5);
    g_.add_edge(e);

    ASSERT_DEATH({g_.remove_edge(e2);},"");
}

TEST_F(GraphTest, NeighborsVertexCollectionsSize)
{
    const vertex v (1);
    initNeighborsCollectionTest(v);
    const set_of_vertices ns = g_.neighbors_set(v);
    const sequence_of_vertices nv = g_.neighbors_sequence(v);

    EXPECT_EQ(ns.size(), 2);
    EXPECT_EQ(nv.size(), 2);
}

TEST_F(GraphTest, NeighborsEdgeCollectionsSize)
{
    const vertex v (1);
    initNeighborsCollectionTest(v);
    const set_of_edges ns = g_.neighbor_edges_set(v);
    const sequence_of_edges ne = g_.neighbor_edges_sequence(v);

    EXPECT_EQ(ns.size(), 2);
    EXPECT_EQ(ne.size(), 2);
}

TEST_F(GraphTest, IsVertexExistsInNeighborsCollection)
{
    const vertex v(1);
    initNeighborsCollectionTest(v);
    const set_of_vertices ns = g_.neighbors_set(v);
    const sequence_of_vertices nv = g_.neighbors_sequence(v);

    auto it_set = ns.find(vertex(3));
    auto it_sequence = std::find(nv.begin(), nv.end(), vertex(2));
    EXPECT_TRUE(it_set != ns.end());
    EXPECT_TRUE(it_sequence != nv.end());
}

TEST_F(GraphTest, ShouldGetRandomEdge)
{
    update(graph_size(10), storage_core_type::BITSETS_FULL);
    const edge e1(3, 5);
    const edge e2(7, 8);
    const edge e3(5, 8);
    const edge e4(2, 6);

    g_.add_edge(e1);
    g_.add_edge(e2);
    g_.add_edge(e3);
    g_.add_edge(e4);

    random_generator generator (time(0));
    const edge randomEdge = g_.random_edge(generator);
    EXPECT_TRUE(g_.edge_exists(randomEdge));
}

TEST_F(GraphTest, RandomlyGetTheSingleEdgeOfGraph)
{
    const edge e (1, 199);

    g_.add_edge(e);
    random_generator generator (time(0));
    const edge randomEdge = g_.random_edge(generator);
    EXPECT_TRUE(g_.edge_exists(randomEdge));
}

TEST_F(GraphTest, GetRandomEdgeNegative)
{
    random_generator generator (time(0));
    ASSERT_DEATH({g_.random_edge(generator);},"");
}

TEST_F(GraphTest, EdgesCollections)
{
    /*g_.add_edge(edge(1, 2));
    g_.add_edge(edge(3, 4));
    g_.add_edge(edge(6, 3));*/

    //const set_of_edges sete = g_.edges_set();
    //const sequence_of_edges seqe = g_.edges_sequence();
    //EXPECT_EQ(sete.size(), 3);
    //EXPECT_EQ(seqe.size(), 3);
}

} // unnamed namespace
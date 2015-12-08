//////////////////////////////////////////////////////////
//     Description:                                     //
//          The following tests used to cover basic     //
//     functionality of erdos_renyi_reader.        //
//                                                      //
//                                                      //
//////////////////////////////////////////////////////////

#include "erdos_renyi_reader.h"
#include "graph.h"

#include "gtest/gtest.h"

// TODO: Need to add checks for read graph internal structures
//       (edge, neighbours collection)
//       to complete fully covering of this component.

namespace
{

class ErdosRenyiReaderTest : public ::testing::Test
{
protected:
    // will be called at the beginning of every GraphTest test.
    virtual void SetUp()
    {
        m_file = "./lib/testing_graphs/graph__N128_p0.3.txt";
        m_reader.get_graph_and_properties_from_file(m_file,
                                                    m_graph,
                                                    m_vertex_count,
                                                    m_prob);
    }

public:
    unsigned get_vertex_count()
    {
        return m_vertex_count;
    }

    double get_probability()
    {
        return m_prob;
    }

    graph_types::graph& get_graph()
    {
        return m_graph;
    }

private:
    erdos_renyi_reader m_reader;
    graph_types::graph m_graph;
    unsigned m_vertex_count;
    std::string m_file;
    double m_prob;
};

TEST_F(ErdosRenyiReaderTest, ShouldCheckTheSizeOfReadGraph)
{
    EXPECT_EQ(get_vertex_count(), 128u);
}

TEST_F(ErdosRenyiReaderTest, ShouldCheckTheProbabilityOfReadGraph)
{
    EXPECT_DOUBLE_EQ(get_probability(), 0.3);
}

TEST_F(ErdosRenyiReaderTest, ShouldCheckSomeConnections)
{
    const auto g = get_graph();
    EXPECT_TRUE(g.edge_exists(graph_types::edge(62, 99)));
    EXPECT_TRUE(g.edge_exists(graph_types::edge(7, 78)));
    EXPECT_TRUE(g.edge_exists(graph_types::edge(10, 24)));
}

TEST(ErdosRenyiReaderThrowTest, ShouldThrowAnExceptionForStandardGraphs)
{
    erdos_renyi_reader r;

    const std::string f ("./lib/testing_graphs/s_graph_N256_p0.3.txt");
    graph_types::graph g;
    unsigned v;
    double p;
    // TODO: Replace with specific exception test statement.
    EXPECT_ANY_THROW({r.get_graph_and_properties_from_file(f, g, v, p);});
}

}

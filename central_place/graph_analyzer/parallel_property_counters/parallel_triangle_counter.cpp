/**
 * @file parallel_property_counters/parallel_triangle_counter.cpp
 * @brief definition of class parallel_triangle_counter.
 */

#include "parallel_triangle_counter.h"
#include "erdos_renyi_reader.h"
#include "graph_constants.h"

#include <iostream>
#include <ctime>
#include <assert.h>

//////////////////////////////////////////////////
//#include <boost/graph/erdos_renyi_generator.hpp>
//#include <boost/random/linear_congruential.hpp>
//////////////////////////////////////////////////

parallel_triangle_counter::parallel_triangle_counter(boost::mpi::communicator& comm,
    const std::string& infile) :
    m_comm(comm),
    m_count(-1),
    m_partition_begin(-1),
    m_partition_end(-1)
{

   ////////////////////////////////////////////////////////////////////////////////////////////////
   //typedef boost::erdos_renyi_iterator<boost::minstd_rand, graph_types::undirected_graph> ERGen;
   //boost::minstd_rand gen;
   //m_graph = graph_types::undirected_graph(ERGen(gen, 2000, 0.3), ERGen(), 2000);
   //m_vertex_count = num_vertices(m_graph);
   ////////////////////////////////////////////////////////////////////////////////////////////////
    erdos_renyi_reader r;
    r.get_graph_and_properties_from_file(infile, m_graph, m_vertex_count, m_probability);
    // TODO: clarify this assert.
    //assert(m_vertex_count == num_vertices(m_graph));
}

void parallel_triangle_counter::count()
{
    init_current_partition();
    //count_on_partition();
    if (0 == m_comm.rank()) {
        accumulate_results();
    } else {
        send_result();
    }
}

void parallel_triangle_counter::init_current_partition()
{
    int partition_size = m_vertex_count / m_comm.size();
    m_partition_begin = m_comm.rank() * partition_size;
    m_partition_end = (m_comm.rank() + 1) * partition_size;
    if(m_comm.rank() == m_comm.size() - 1) {
        m_partition_end = m_vertex_count;
    }
    /////////////////////////////////////////////////////////////////////
    //  std::cout << "Initializing graph partition for process: #"
    //            << m_comm.rank() << " interval ["
    //            << m_partition_begin << " "<< m_partition_end << ")\n";
    /////////////////////////////////////////////////////////////////////
}

void parallel_triangle_counter::count_on_partition()
{
    using namespace graph_types;

    int vert_index = 0;
    const auto size = m_graph.size();
    for (vertex vert_id = constants::VERTEX_0;
        vert_id < size; ++vert_id, ++vert_index) {

        if(m_partition_begin <= vert_index && m_partition_end > vert_index) {
            int curr_vert_count = 0;
            const sequence_of_vertices neighbours = m_graph.neighbors_sequence(vert_id);

            auto first_adj_it = neighbours.begin();
            auto second_adj_it = neighbours.begin();
            const auto adj_end = neighbours.end();

            for ( ; first_adj_it != adj_end; ++first_adj_it ) {
                for ( ; second_adj_it != adj_end; ++second_adj_it) {
                    if (*first_adj_it != *second_adj_it &&
                        m_graph.edge_exists(*first_adj_it, *second_adj_it))
                        ++curr_vert_count;
                }
            }
            m_count += curr_vert_count / 2;
        }
    }
}

void parallel_triangle_counter::send_result()
{
    assert(0 != m_comm.rank());
    m_comm.send(0, m_comm.rank(), m_count);
}

void parallel_triangle_counter::accumulate_results()
{
    assert(0 == m_comm.rank());
    int received = 0;
    for(int i = 1; i < m_comm.size(); ++i) {
        m_comm.recv(i, i, received);
        m_count += received;
    }
    m_count /= 3;
}

void parallel_triangle_counter::write_results() const
{
    if(0 == m_comm.rank())
    {
        std::cout << "Parallel computing is done. " << std::endl
            << "Parallel processes count: " << m_comm.size() << std::endl
            << "Graph vertices count: " << m_vertex_count << std::endl
            << "Graph probability: " << m_probability << std::endl
            << "Triangles count: " << m_count << std::endl;
    }
}


/**
 * @file parallel_property_counters/parallel_triangle_counter.h
 * @brief declaration of class parrallel_property_counter.
 */

#pragma once

#include "types.h"
#include <boost/mpi.hpp>
#include "graph.h"

/**
 * @class parallel_triangle_counter
 * @brief this class is used for parallely counting triangles in read graph
 */
class parallel_triangle_counter
{
public:
    /**
     * @brief Constructor of parrallel_property_counter
     */
    parallel_triangle_counter(boost::mpi::communicator& comm, const std::string& infile);

public:
    /**
     * @brief Runs main count flow
     */
    void count();

public:
    /**
     * @brief Writes results.
     */
    void write_results() const;

private:
    void init_current_partition();
    void count_on_partition();
    void send_result();
    void accumulate_results();

private:
    graph_types::graph m_graph;
    unsigned m_vertex_count;
    double m_probability;
    int m_count;
    int m_partition_begin;
    int m_partition_end;
    boost::mpi::communicator& m_comm;
};

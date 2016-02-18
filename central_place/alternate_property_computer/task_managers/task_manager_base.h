/**
 * @file task_managers/task_manager_base.h
 * @brief declaration of task_manager_base class.
 */

#pragma once

#include "types.h"
#include "graph_types.h"
#include "graph.h"
#include "igraph_task_manager.h"

#include <boost/mpi.hpp>
#include <fstream>

class randomizator_base;
class property_counter_base;

/**
 * @class task_manager_base
 * @brief base class for task managers.
 */
class task_manager_base : public igraph_task_manager
{
public:
    /**
     * @brief Inits task manager.
     * @param g Undirected graph.
     * @param m Mu list
     * @param s_c Step count
     * @param r Randomization type
     * @param p Alternate property type.
     */
    void init(const graph_types::graph& g,
        const mu_list& m, unsigned s_c, const randomization_type r,
        const alternate_property_type p);

private:
    /**
     * @brief Treats status information.
     * @param info Information to treat.
     */
    virtual void treat_status_information(const persent_to_mu& info) = 0;

public:
    /**
     * @brief Gets results.
     */
    const calculation_results& get_results() const;

protected:
    bool check_to_assume_step(int delta, double mu) const;

protected:
    void calculate_for_single_mu_by_pass_count(
        single_results_list& c_r, double mu);

private:
    void create_status_info_and_send_to_treat(const int step,
        const int pass_step, const double mu);

protected:
    void calculate_for_single_mu(single_results_list& c_r,
        double mu, int pass_step);

protected:
    void calculate_initial_non_existing_edges();

private:
    void calculate_initial_alternate_property_count();

protected:
    enum mpi_tag {
        PROCESS_IS_NEEDED = 1,
        GRAPH = 2,
        ALTERNATE_PROPERTY_INITIAL_COUNT = 3,
        STEP_COUNT = 4,
        PASS_COUNT = 5,
        RANDOMIZATION_TYPE = 6,
        ALTERNATE_PROPERTY_TYPE = 7,
        MUS = 8,
        STATUS_TAGS = 9,
        MU_START = 100,
        STATUS_START = 1000
    };

protected:
    bool m_inited;
    boost::mpi::communicator& m_world;
    graph_types::graph m_current_graph;
    mu_list m_mu_list;
    unsigned m_step_count;
    // TODO: pass count must be got from program arguments.
    //       for now it will just set to 10.
    unsigned m_pass_count; 
    randomization_type m_randomizator_type;
    randomizator_base* m_randomizator;
    property_counter_base* m_counter;
    unsigned m_initial_property_count;
    unsigned m_current_property_count;
    graph_types::sequent_null_edges m_initial_non_existing_edges;
    graph_types::sequent_null_edges m_current_non_existing_edges;
    calculation_results m_results;

public:
    /**
     * @brief Constructor
     * @param world World of mpi
     */
    task_manager_base(boost::mpi::communicator& world,
        std::ofstream& logger);

public:
    /**
     * @brief Destructor
     */
    virtual ~task_manager_base();
};

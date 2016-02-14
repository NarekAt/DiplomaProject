/**
 * @file mediator/mediator.h
 * @brief declaration of class mediator.
 */

#pragma once

#include "types.h"
#include "graph.h"
#include <fstream>
#include <boost/mpi.hpp>

class task_manager_base;

/**
 * @class mediator
 * @brief this class is used for managing interaction
 *        between input, task_manager and output interfaces.
 * @note Singleton class.
 */
class mediator
{
    /// @name mediator base public interface
    /// @{
public:
    /**
     * @brief Inits mediator
     * @param a_n_v process arguments map.
     * @note must be called before run() function, and only one time.
     */
    void init(const arg_name_to_value_map& a_n_v);

public:
    /**
     * @brief Runs mediator
     * @param world mpi communicator.
     * @note Before call of this function init() must be called.
     */
    void run(boost::mpi::communicator& world);

public:
    /**
     * @brief Writes came single results list.
     * @param s_r Single results list.
     * @param mu Mu of results
     */
    void write_results(const single_results_list& s_r, double mu) const;

private:
    /**
     * @brief Uses task manager for initing it, run, get result
     *        and send results to output.
     * @param t_m Task manager
     * @pre must not be used for secondary process task manager.
     */
    void run_task_manager_and_send_to_output(task_manager_base& t_m);

private:
    bool m_inited;
    graph_types::graph m_graph;
    mu_list m_mu_list;
    unsigned m_step_count;
    randomization_type m_randomization_type;
    alternate_property_type m_alternate_property_type;
    PropertyComputerType m_graph_item_property_type;
    boost::mpi::communicator m_world;
    unsigned m_vertex_count;
    double m_probability;
    std::ofstream& m_logger;
    /// @}

    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static mediator& get_instance();

public:
    /**
     * @brief Intstantiates singletone object.
     */
    static void instantiate(std::ofstream& logger);

public:
    /**
     * @brief Destroys singletone object.
     */
    static void destroy();

private:
    static mediator* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    mediator(std::ofstream& logger);

public:
    /**
     * @brief Destructor.
     */
    ~mediator() = default;
private:
    mediator(const mediator&) = delete;
    mediator& operator=(const mediator&) = delete;
    /// @}
};

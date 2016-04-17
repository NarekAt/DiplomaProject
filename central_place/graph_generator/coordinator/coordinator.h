/**
 * @file coordinator/coordinator.h
 * @brief declaration of class coordinator.
 */

#pragma once

#include "types.h"
#include "graph_types.h"
#include <boost/mpi.hpp>
#include <fstream>

/**
 * @class coordinator
 * @brief this class is used for coordinating interaction
 *        between generating and writing interfaces.
 * @note Singleton class.
 */
class coordinator
{
    /// @name coordinator base public interface
    /// @{
public:
    /**
     * @brief Inits coordinator
     * @param a_n_v process arguments map.
     * @note must be called before run() function, and only one time.
     */
    void init(const arg_name_to_value_map& a_n_v);

public:
    /**
     * @brief Runs coordinator
     * @note Before call of this function init() must be called.
     */
    void run();

private:
    bool m_inited;
    std::string m_model;
    unsigned m_vertex_count;
    double m_probability;
    unsigned m_num_edges;
    graph_types::storage_core_type m_core_type;
    std::string m_output_file;
    std::ofstream& m_logger;
    /// @}

    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static coordinator& get_instance();

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
    static coordinator* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    coordinator(std::ofstream& logger);

public:
    /**
     * @brief Destructor.
     */
    ~coordinator() = default;
private:
    coordinator(const coordinator&) = delete;
    coordinator& operator=(const coordinator&) = delete;
    /// @}
};

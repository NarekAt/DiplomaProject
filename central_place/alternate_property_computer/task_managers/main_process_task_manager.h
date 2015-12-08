/**
 * @file task_managers/main_process_task_manager.h
 * @brief declaration of main_process_task_manager class.
 */

#pragma once

#include "task_manager_base.h"

/**
 * @class main_process_task_manager
 * @brief main process task manager
 *        rules secondary processes.
 */
class main_process_task_manager : public task_manager_base
{
public:
    /**
     * @brief Runs task manager
     */
    virtual void run();

private:
    /**
     * @brief Treats status information.
     * @param info Information to treat.
     */
    virtual void treat_status_information(const persent_to_mu& info);

private:
    /**
     * @brief Sends needed ingredients to secondary processes.
     */
    void send_ingredients_to_precesses();

private:
    /**
     * @brief Sends needed ingredients to the secondary process.
     * @param p_id Id of process to send ingredients.
     * @param mus Mu list for which secondary process must made
     *        calculations.
     * @param s_t Status tags per process.
     */
    void send_ingredients(unsigned p_id, 
        const tag_to_mu_map& mus, const status_tags& s_t) const;

private:
    /**
     * @brief Colculate mu count per process.
     */
    void colculate_process_to_mu_count();

private:
    /**
     * @brief Recieves results from secondary processes.
     */
    void receive_results_from_processes();

private:
    process_to_mu_count m_process_to_mu_count;
    process_to_status_tags m_process_to_status_tags;
public:
    /**
     * @brief Constructor
     * @param world World of mpi
     */
    main_process_task_manager(boost::mpi::communicator& world,
        std::ofstream& logger);
};

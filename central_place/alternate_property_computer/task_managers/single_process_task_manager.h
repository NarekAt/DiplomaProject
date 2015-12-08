/**
 * @file task_managers/single_process_task_manager.h
 * @brief declaration of single_process_task_manager class.
 */

#pragma once

#include "task_manager_base.h"

/**
 * @class single_process_task_manager
 * @brief single process task manager
 */
class single_process_task_manager : public task_manager_base
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

public:
    /**
     * @brief Constructor
     * @param world World of mpi
     */
    single_process_task_manager(boost::mpi::communicator& world,
        std::ofstream& logger);
};

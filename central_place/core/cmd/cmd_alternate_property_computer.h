#pragma once

/**
 * @file cmd_alternate_property_computer.h
 * @brief declaration of class 
 *              cmd_alternate_property_computer
 * @author Hayk Khachatryan
 */

#include "cmd_base.h"

class cmd_arg_string;

/**
 * @class cmd_alternate_property_computer
 * @brief Command to work with alternate property computer.
 */
class cmd_alternate_property_computer : public cmd::cmd_base
{
public:
    /**
     * @brief Makes execution of alternate_property_computer command.
     */
    virtual void execute();

private:
    cmd_arg_string* m_process_count;
    cmd_arg_string* m_randomization_type;
    cmd_arg_string* m_alternate_property_type;
    cmd_arg_string* m_step_count;
    cmd_arg_string* m_graph_file;
    cmd_arg_string* m_mu_file;

public:
    /**
     * @brief Constructor.
     */
    cmd_alternate_property_computer();
};

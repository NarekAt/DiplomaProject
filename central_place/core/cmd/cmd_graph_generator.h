#ifndef CMD_graph_generator_H
#define CMD_graph_generator_H

/**
 * @file cmd_graph_generator.h
 * @brief declaration of class 
 *              cmd_graph_generator
 * @author Hayk Khachatryan
 */

#include "cmd_base.h"

class cmd_arg_string;

/**
 * @class cmd_graph_generator
 * @brief Command to work with graph generator.
 */
class cmd_graph_generator : public cmd::cmd_base
{
public:
    /**
     * @brief Makes execution of graph_generator command.
     */
    virtual void execute();

private:
    cmd_arg_string* m_size;
    cmd_arg_string* m_probability;
    cmd_arg_string* m_core_type;
    cmd_arg_string* m_output_file;

public:
    /**
     * @brief Constructor.
     */
    cmd_graph_generator();
};

#endif //graph_generator_H

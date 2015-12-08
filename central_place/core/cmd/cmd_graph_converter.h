#ifndef CMD_GRAPH_CONVERTER_H
#define CMD_GRAPH_CONVERTER_H

/**
 * @file cmd_graph_converter.h
 * @brief declaration of class 
 *              cmd_graph_converter
 * @author Hayk Khachatryan
 */

#include "cmd_base.h"

class cmd_arg_string;

/**
 * @class cmd_graph_converter
 * @brief Command to work with graph converter.
 */
class cmd_graph_converter : public cmd::cmd_base
{
public:
    /**
     * @brief Makes execution of graph_converter command.
     */
    virtual void execute();

private:
    cmd_arg_string* m_flag;
    cmd_arg_string* m_file_from;
    cmd_arg_string* m_file_to;

public:
    /**
     * @brief Constructor.
     */
    cmd_graph_converter();
};

#endif //GRAPH_CONVERTER_H

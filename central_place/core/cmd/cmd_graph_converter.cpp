#include "cmd_graph_converter.h"
#include "cmd_arg_string.h"
#include "cmd_exception.h"
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>

void cmd_graph_converter::execute()
{
    int pid = fork();
    if (-1 == pid) {
        std::string message("cannot fork program");
        throw cmd::exception(message);
    } else if (0 == pid) {
        std::string executable = std::string("./graph_converter.exe");
        char* exec_args[] = { const_cast<char*>(executable.c_str()),
            const_cast<char*>(m_flag->get_value().c_str()),
            const_cast<char*>(m_file_from->get_value().c_str()),
            const_cast<char*>(m_file_to->get_value().c_str()), NULL };
        if (-1 == execvp(executable.c_str(), exec_args)) {
            std::cout << strerror(errno) << std::endl;
            exit(0);
        }
    }
}

cmd_graph_converter::cmd_graph_converter() 
    : cmd_base("graph_converter")
{
    m_flag = new cmd_arg_string("flag");
    add_argument(m_flag);
    m_file_from = new cmd_arg_string("file_from");
    add_argument(m_file_from);
    m_file_to = new cmd_arg_string("file_to");
    add_argument(m_file_to);
}

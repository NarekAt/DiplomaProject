#include "cmd_graph_generator.h"
#include "cmd_arg_string.h"
#include "cmd_exception.h"
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>

void cmd_graph_generator::execute()
{
    int pid = fork();
    if (-1 == pid) {
        std::string message("cannot fork program");
        throw cmd::exception(message);
    } else if (0 == pid) {
        std::string executable = std::string("./graph_generator.exe");
        const char* arg0 = "graph_generator.exe";
        const char* arg1 = "--size";
        const char* arg2 = m_size->get_value().c_str();
        const char* arg3 = "--probability";
        const char* arg4 = m_probability->get_value().c_str();
        const char* arg5 = "--core_type";
        const char* arg6 = m_core_type->get_value().c_str();
        const char* arg7 = "--output_file";
        const char* arg8 = m_output_file->get_value().c_str();
        if (-1 == execlp(executable.c_str(), arg0, arg1, arg2, arg3, arg4,
            arg5, arg6, arg7, arg8, NULL)) {
            std::cout << strerror(errno) << std::endl;
            exit(0);
        }
    }
}

cmd_graph_generator::cmd_graph_generator()
    : cmd_base("graph_generator")
{
    m_size = new cmd_arg_string("size");
    add_argument(m_size);
    m_probability = new cmd_arg_string("probability");
    add_argument(m_probability);
    m_core_type = new cmd_arg_string("core_type");
    add_argument(m_core_type);
    m_output_file = new cmd_arg_string("output_file");
    add_argument(m_output_file);
}

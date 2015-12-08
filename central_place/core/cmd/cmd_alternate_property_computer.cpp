#include "cmd_alternate_property_computer.h"
#include "cmd_arg_string.h"
#include "cmd_exception.h"
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>

void cmd_alternate_property_computer::execute()
{
    int pid = vfork();
    if (-1 == pid) {
        std::string message("cannot fork program");
        throw cmd::exception(message);
    } else if (0 == pid) {
       pid = vfork();
       if (-1 == pid) {
            std::string message("cannot fork program");
            throw cmd::exception(message);
       } else if (0 != pid) {
           exit(0);
       }
       std::string executable = std::string("/usr/local/bin/mpirun");
       const char* arg0 = "mpirun";
       std::string arg1_str = std::string("-np=") + m_process_count->get_value();
       const char* arg1 = arg1_str.c_str();
       const char* arg2 = "./alternate_property_computer.exe";
       const char* arg3 = "--randomization_type";
       const char* arg4 = m_randomization_type->get_value().c_str();
       const char* arg5 = "--graph_file";
       const char* arg6 = m_graph_file->get_value().c_str();
       const char* arg7 = "--mu_file";
       const char* arg8 = m_mu_file->get_value().c_str();
       const char* arg9 = "--step_count";
       const char* arg10 = m_step_count->get_value().c_str();
       const char* arg11 = "--alternate_property_type";
       const char* arg12 = m_alternate_property_type->get_value().c_str();
        if (-1 == execlp(executable.c_str(), arg0, arg1, arg2, arg3,
            arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, NULL)) {
            std::cout << strerror(errno) << std::endl;
            exit(0);
        }
        exit(0);
    }
}

cmd_alternate_property_computer::cmd_alternate_property_computer() 
    : cmd_base("alternate_property_computer")
{
    m_process_count = new cmd_arg_string("np");
    add_argument(m_process_count);
    m_randomization_type = new cmd_arg_string("randomization_type");
    add_argument(m_randomization_type);
    m_alternate_property_type = new cmd_arg_string("alternate_property_type");
    add_argument(m_alternate_property_type);
    m_step_count = new cmd_arg_string("step_count");
    add_argument(m_step_count);
    m_graph_file = new cmd_arg_string("graph_file");
    add_argument(m_graph_file);
    m_mu_file = new cmd_arg_string("mu_file");
    add_argument(m_mu_file);
}

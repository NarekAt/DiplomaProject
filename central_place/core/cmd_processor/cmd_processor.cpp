#include "cmd_processor.h"

/**
 * @file cmd_processor.cpp
 * @brief definition of class 
 *              cmd_processor
 * @author Hayk Khachatryan
 */

#include "cmd_base.h"
#include "cmd_exception.h"
#include <sstream>
#include <assert.h>

namespace cmd
{

cmd_processor* cmd_processor::s_instance = nullptr;

void cmd_processor::add_command(cmd_base* cmd)
{
    assert(nullptr != cmd);
    assert(m_commands.end() == m_commands.find(cmd->get_name()));
    m_commands.insert(std::make_pair(cmd->get_name(), cmd));
}

namespace {

std::vector<std::string> split_to_tokens(const std::string& line)
{
    std::istringstream is(line);
    std::vector<std::string> tokens;
    std::string token;
    is >> token;
    while (!token.empty()) {
        tokens.push_back(token);
        token.clear();
        is >> token;
    }
    return tokens;
}

}

void cmd_processor::parse_and_execute_command(const std::string& c_l)
{
    std::vector<std::string> tokens = split_to_tokens(c_l);
    assert(!tokens.empty());
    std::string cmd_name = tokens[0];
    tokens.erase(tokens.begin());
    auto it = m_commands.find(cmd_name);
    if (m_commands.end() == it) {
        std::string message = 
            std::string("There is no command with name '")
            + cmd_name + std::string("'");
        throw exception(message);
    }
    parse_arg_list(it->second, tokens);
    (it->second)->execute();
    (it->second)->reset();
}

void cmd_processor::parse_arg_list(cmd_base* cmd
    , const std::vector<std::string>& a_l)
{
    assert(nullptr != cmd);
    if (0 != a_l.size()%2) {
        std::string message("Invalid argument list");
        throw exception(message);
    }
    for (auto it = a_l.begin(); it != a_l.end(); it+=2) {
        if ('-' != (*it)[0] || 1 == it->size()) {
            std::string message = 
                std::string("Invalid argument name '")
                + *it + std::string("'");
            throw exception(message);
        }
        cmd->set_arg_value((*it).substr(1), *(it + 1));
    }
}

cmd_processor& cmd_processor::get_instance()
{
    assert(s_instance != nullptr);
    return *s_instance;
}

void cmd_processor::instantiate()
{
    assert(s_instance == nullptr);
    s_instance = new cmd_processor();
}

void cmd_processor::destroy()
{
    assert(s_instance != nullptr);
    delete s_instance;
    s_instance = nullptr;
}

cmd_processor::~cmd_processor()
{
    for (auto& v : m_commands) {
        delete v.second;
    }
    m_commands.clear();
}

}

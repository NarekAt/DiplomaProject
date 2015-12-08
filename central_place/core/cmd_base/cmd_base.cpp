#include "cmd_base.h"

/**
 * @file cmd_base.cpp
 * @brief definition of class 
 *              cmd_base
 * @author Hayk Khachatryan
 */

#include "cmd_arg_base.h"
#include "cmd_exception.h"
#include <assert.h>

namespace cmd
{

const std::string& cmd_base::get_name() const
{
    return m_name;
}

bool cmd_base::is_equal(const std::string& n) const
{
    return n == m_name;
}

void cmd_base::add_argument(cmd_arg_base* a)
{
    assert(nullptr != a);
    assert(m_args.end() == m_args.find(a->get_name()));
    m_args.insert(std::make_pair(a->get_name(), a));
}

void cmd_base::set_arg_value(const std::string& arg_name
    , const std::string& arg_value)
{
    assert("" != arg_name);
    auto it = m_args.find(arg_name);
    if (m_args.end() == it) {
        std::string message = std::string("Command '")
            + m_name + std::string("' hasn't argument with name '")
            + arg_name + std::string("'.");
        throw exception(message);
    }
    (it->second)->set_value(arg_value);
}

void cmd_base::reset()
{
    for (auto& v : m_args) {
        (v.second)->set_specified(false);
        (v.second)->reset();
    }
}

cmd_base::cmd_base(const std::string& name)
    : m_name(name)
{
    assert("" != name);
}

cmd_base::~cmd_base()
{
    for (auto& v : m_args) {
        delete v.second;
    }
    m_args.clear();
}

}

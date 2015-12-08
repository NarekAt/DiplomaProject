#include "cmd_arg_string.h"

/**
 * @file cmd_arg_string.h
 * @brief definition of class 
 *              cmd_arg_string
 * @author Hayk Khachatryan
 */

#include "cmd_exception.h"
#include <boost/lexical_cast.hpp>

std::string cmd_arg_string::get_value() const
{
    return m_value;
}

std::string cmd_arg_string::get_default_value() const
{
    return m_default_value;
}

void cmd_arg_string::set_value(const std::string& v)
{
    m_value = v;
}

void cmd_arg_string::reset()
{
    set_specified(false);
    m_value = m_default_value;
}

cmd_arg_string::cmd_arg_string(std::string name
    , std::string default_value)
    : cmd_arg_base(name)
    , m_default_value(default_value)
    , m_value(default_value)
{
}

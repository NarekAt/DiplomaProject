#include "cmd_arg_double.h"

/**
 * @file cmd_arg_double.h
 * @brief definition of class 
 *              cmd_arg_double
 * @author Hayk Khachatryan
 */

#include "cmd_exception.h"
#include <boost/lexical_cast.hpp>

double cmd_arg_double::get_value() const
{
    return m_value;
}

double cmd_arg_double::get_default_value() const
{
    return m_default_value;
}

void cmd_arg_double::set_value(const std::string& v)
{
    try {
        m_value = boost::lexical_cast<double>(v); 
    } catch (const boost::bad_lexical_cast&) {
        std::string message = 
            std::string("Please provide valid double value for '")
            + get_name() + std::string("' argument.");
        throw cmd::exception(message);
    }
}

void cmd_arg_double::reset()
{
    set_specified(false);
    m_value = m_default_value;
}

cmd_arg_double::cmd_arg_double(std::string name, double default_value)
    : cmd_arg_base(name)
    , m_default_value(default_value)
    , m_value(default_value)
{
}

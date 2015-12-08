#include "cmd_arg_int.h"

/**
 * @file cmd_arg_int.h
 * @brief definition of class 
 *              cmd_arg_int
 * @author Hayk Khachatryan
 */

#include "cmd_exception.h"
#include <boost/lexical_cast.hpp>

int cmd_arg_int::get_value() const
{
    return m_value;
}

int cmd_arg_int::get_default_value() const
{
    return m_default_value;
}

void cmd_arg_int::set_value(const std::string& v)
{
    try {
        m_value = boost::lexical_cast<int>(v); 
    } catch (const boost::bad_lexical_cast&) {
        std::string message = 
            std::string("Please provide valid integer value for '")
            + get_name() + std::string("' argument.");
        throw cmd::exception(message);
    }
}

void cmd_arg_int::reset()
{
    set_specified(false);
    m_value = m_default_value;
}

cmd_arg_int::cmd_arg_int(std::string name, int default_value)
    : cmd_arg_base(name)
    , m_default_value(default_value)
    , m_value(default_value)
{
}

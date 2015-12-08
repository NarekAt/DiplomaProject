#include "cmd_arg_bool.h"

/**
 * @file cmd_arg_bool.h
 * @brief definition of class 
 *              cmd_arg_bool
 * @author Hayk Khachatryan
 */

#include "cmd_exception.h"

bool cmd_arg_bool::get_value() const
{
    return m_value;
}

bool cmd_arg_bool::get_default_value() const
{
    return m_default_value;
}

void cmd_arg_bool::set_value(const std::string& v)
{
    if ("true" == v || "t" == v || "1" == v) {
        m_value = true;
    } else if ("false" == v || "f" == v || "0" == v) {
        m_value = false;
    } else {
        std::string message = 
            std::string("Please provide valid boolean value for '")
            + get_name() + std::string("' argument.");
        throw cmd::exception(message);
    }
}

void cmd_arg_bool::reset()
{
    set_specified(false);
    m_value = m_default_value;
}

cmd_arg_bool::cmd_arg_bool(std::string name, bool default_value)
    : cmd_arg_base(name)
    , m_default_value(default_value)
    , m_value(default_value)
{
}

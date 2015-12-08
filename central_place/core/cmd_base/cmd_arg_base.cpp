#include "cmd_arg_base.h"

/**
 * @file cmd_arg_base.cpp
 * @brief definition of class 
 *              cmd_arg_base
 * @author Hayk Khachatryan
 */

#include <assert.h>

namespace cmd
{

bool cmd_arg_base::is_specified() const
{
    return m_is_specified;
}

void cmd_arg_base::set_specified(bool s)
{
    m_is_specified = s;
}

const std::string& cmd_arg_base::get_name() const
{
    return m_name;
}

bool cmd_arg_base::is_equal(const std::string& n) const
{
    return n == m_name;
}

cmd_arg_base::cmd_arg_base(const std::string& name)
    : m_name(name)
    , m_is_specified(false)
{
    assert(name != "");
}

cmd_arg_base::~cmd_arg_base()
{
}

}

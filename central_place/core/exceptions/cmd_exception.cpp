#include "cmd_exception.h"

/**
 * @file cmd_exception.cpp
 * @brief definition of class 
 *              exception
 * @author Hayk Khachatryan
 */

#include <assert.h>

namespace cmd
{

const std::string& exception::get_message() const
{
    return m_message;
}

exception::exception(const std::string& m)
    : m_message(m)
{
    assert("" != m);
}

exception::~exception()
{
}

}

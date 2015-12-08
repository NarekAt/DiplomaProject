/**
 * @file exceptions/exception_base.cpp
 * @brief definition of class exception
 */

#include "exception_base.h"

#include <assert.h>

const std::string& exception_base::get_message() const
{
    return m_message;
}

exception_base::exception_base(const std::string& m)
    : m_message(m)
{
    assert("" != m);
}

exception_base::~exception_base()
{
}

/**
 * @file exceptions/exception_base.h 
 * @brief declaration of class exception
 */

#pragma once

#include <string>

/**
 * @class exception_base
 * @brief base exception system
 */
class exception_base
{
public:
    /**
     * @brief Gets message of exception.
     */
    const std::string& get_message() const;

private:
    const std::string m_message;

public:
    /**
     * @brief Constructor.
     * @param m Message of exception.
     */
    exception_base(const std::string& m);

public:
    /**
     * @brief Virtual Destructor.
     */
    virtual ~exception_base();
}; // end of class exception


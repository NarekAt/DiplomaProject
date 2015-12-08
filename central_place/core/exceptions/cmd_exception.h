#ifndef CMD_CMD_EXCEPTION_H
#define CMD_CMD_EXCEPTION_H

/**
 * @file cmd_exception.h
 * @brief declaration of class 
 *              exception
 * @author Hayk Khachatryan
 */

#include <string>

/**
 * @namespace cmd
 * @brief command infrastructure
 *        namespace
 */
namespace cmd
{

/**
 * @class exception
 * @brief exception system for
 *        cmd level exceptions.
 */
class exception
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
    exception(const std::string& m);

public:
    /**
     * @brief Virtual Destructor.
     */
    virtual ~exception();
}; // end of class exception

} // end of namespace cmd

#endif //CMD_CMD_EXCEPTION_H

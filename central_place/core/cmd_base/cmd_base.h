#ifndef CMD_CMD_BASE_H
#define CMD_CMD_BASE_H

/**
 * @file cmd_base.h
 * @brief declaration of class 
 *              cmd_base
 * @author Hayk Khachatryan
 */

#include <string>
#include <map>

/**
 * @namespace cmd
 * @brief command infrastructure
 *        namespace
 */
namespace cmd
{

class cmd_arg_base;

/**
 * @class cmd_base
 * @brief Abstract base class
 *        commands
 */
class cmd_base
{
public:
    /**
     * @brief Gets command's name.
     * @return Constant access to
     *         command's name.
     */
    const std::string& get_name() const;

public:
    /**
     * @brief Checks if command has
     *        same name.
     * @param n Name to compare.
     * @return true if argument's name
     *         is equal to the given name.
     */
    bool is_equal(const std::string& n) const;

public:
    /**
     * @brief Adds argument to argument list
     *        of command.
     * @param a Argument to add.
     */
    void add_argument(cmd_arg_base* a);

public:
    /**
     * @brief Sets arg's value.
     * @param arg_name Name of argument to be set.
     * @param arg_value Value to set.
     */
    void set_arg_value(const std::string& arg_name
        , const std::string& arg_value);
public:
    /**
     * @brief Resets all argumets of command.
     */
    void reset();

public:
    /**
     * @brief pure virtual function to make execution
     *        of command.
     */
    virtual void execute() = 0;

private:
    const std::string m_name;
    std::map<std::string, cmd_arg_base*> m_args;

public:
    /**
     * @brief Constructor.
     * @param name Name of command.
     */
    cmd_base(const std::string& name);

public:
    /**
     * @brief Virtual destructor.
     */
    ~cmd_base();

private:
    cmd_base(const cmd_base&) = delete;
    cmd_base& operator=(const cmd_base&) = delete;
}; // end of class cmd_base

} // end of namespace cmd

#endif //CMD_CMD_BASE_H

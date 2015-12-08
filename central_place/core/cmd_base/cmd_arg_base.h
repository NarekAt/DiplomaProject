#ifndef CMD_CMD_ARG_BASE_H
#define CMD_CMD_ARG_BASE_H

/**
 * @file cmd_arg_base.h
 * @brief declaration of class 
 *              cmd_arg_base
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
 * @class cmd_arg_base
 * @brief Abstract base class
 *        for command args.
 */
class cmd_arg_base
{
public:
    /**
     * @brief Returns true if argument
     *        is specified, otherwise 
     *        returns false.
     */
    bool is_specified() const;

public:
    /**
     * @brief Sets specified flag
     *        of argument.
     * @param s flag to set.
     */
    void set_specified(bool s);

public:
    /**
     * @brief Gets argument's name.
     * @return Constant access to
     *         argument name.
     */
    const std::string& get_name() const;

public:
    /**
     * @brief Checks if argument has
     *        same name.
     * @param n Name to compare.
     * @return true if argument's name
     *         is equal to the given name.
     */
    bool is_equal(const std::string& n) const;

public:
    /**
     * @brief Pure virtual function to set
     *        argument's value.
     * @param v Value to set.
     */
    virtual void set_value(const std::string& v) = 0;

public:
    /**
     * @brief Pure virtual function to reset
     *        argument.
     */
    virtual void reset() = 0;

private:
    const std::string m_name;
    bool m_is_specified;

public:
    /**
     * @brief Constructor.
     * @param name Name of Argument.
     */
    cmd_arg_base(const std::string& name);

public:
    /**
     * @brief Virtual destructor
     */
    virtual ~cmd_arg_base();

private:
    cmd_arg_base(const cmd_arg_base&) = delete;
    cmd_arg_base& operator=(const cmd_arg_base&) = delete;
}; // end of class cmd_arg_base

} // end of namespace cmd

#endif //CMD_CMD_ARG_BASE_H

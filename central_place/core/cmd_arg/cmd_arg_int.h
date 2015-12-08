#ifndef CMD_ARG_int_H
#define CMD_ARG_int_H

/**
 * @file cmd_arg_int.h
 * @brief declaration of class 
 *              cmd_arg_int
 * @author Hayk Khachatryan
 */

#include "cmd_arg_base.h"

/**
 * @class cmd_arg_int
 * @brief Keeps integer command argument.
 */
class cmd_arg_int : public cmd::cmd_arg_base
{
public:
    /**
     * @brief Gets integer argument's value.
     */
    int get_value() const;

public:
    /**
     * @brief Gets integer argument's default value.
     */
    int get_default_value() const;

public:
    /**
     * @brief Sets integer argument's value from string.
     */
    virtual void set_value(const std::string& v);

public:
    /**
     * @brief Resets integer argument.
     */
    virtual void reset();

private:
    int m_value;
    int m_default_value;

public:
    /**
     * @brief Constructor.
     * @param name Name of integer argument.
     * @param default_value Default value.
     */
    cmd_arg_int(std::string name, int default_value = 0);
}; // end of class cmd_arb_int

#endif //CMD_ARG_int_H

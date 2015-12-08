#ifndef CMD_ARG_double_H
#define CMD_ARG_double_H

/**
 * @file cmd_arg_double.h
 * @brief declaration of class 
 *              cmd_arg_double
 * @author Hayk Khachatryan
 */

#include "cmd_arg_base.h"

/**
 * @class cmd_arg_double
 * @brief Keeps double command argument.
 */
class cmd_arg_double : public cmd::cmd_arg_base
{
public:
    /**
     * @brief Gets double argument's value.
     */
    double get_value() const;

public:
    /**
     * @brief Gets double argument's default value.
     */
    double get_default_value() const;

public:
    /**
     * @brief Sets double argument's value from string.
     */
    virtual void set_value(const std::string& v);

public:
    /**
     * @brief Resets double argument.
     */
    virtual void reset();

private:
    double m_value;
    double m_default_value;

public:
    /**
     * @brief Constructor.
     * @param name Name of double argument.
     * @param default_value Default value.
     */
    cmd_arg_double(std::string name, double default_value = 0.0);
}; // end of class cmd_arb_double

#endif //CMD_ARG_double_H

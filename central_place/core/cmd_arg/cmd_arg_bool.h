#ifndef CMD_ARG_BOOL_H
#define CMD_ARG_BOOL_H

/**
 * @file cmd_arg_bool.h
 * @brief declaration of class 
 *              cmd_arg_bool
 * @author Hayk Khachatryan
 */

#include "cmd_arg_base.h"

/**
 * @class cmd_arg_bool
 * @brief Keeps boolean command argument.
 */
class cmd_arg_bool : public cmd::cmd_arg_base
{
public:
    /**
     * @brief Gets boolean argument's value.
     */
    bool get_value() const;

public:
    /**
     * @brief Gets boolean argument's default value.
     */
    bool get_default_value() const;

public:
    /**
     * @brief Sets boolean argument's value from string.
     */
    virtual void set_value(const std::string& v);

public:
    /**
     * @brief Resets boolean argument.
     */
    virtual void reset();

private:
    bool m_value;
    bool m_default_value;

public:
    /**
     * @brief Constructor.
     * @param name Name of boolean argument.
     * @param default_value Default value.
     */
    cmd_arg_bool(std::string name, bool default_value = false);
}; // end of class cmd_arb_bool

#endif //CMD_ARG_BOOL_H

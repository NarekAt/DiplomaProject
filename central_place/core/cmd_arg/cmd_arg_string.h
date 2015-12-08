#ifndef CMD_ARG_string_H
#define CMD_ARG_string_H

/**
 * @file cmd_arg_string.h
 * @brief declaration of class 
 *              cmd_arg_string
 * @author Hayk Khachatryan
 */

#include "cmd_arg_base.h"

/**
 * @class cmd_arg_string
 * @brief Keeps string command argument.
 */
class cmd_arg_string : public cmd::cmd_arg_base
{
public:
    /**
     * @brief Gets string argument's value.
     */
    std::string get_value() const;

public:
    /**
     * @brief Gets string argument's default value.
     */
    std::string get_default_value() const;

public:
    /**
     * @brief Sets string argument's value from string.
     */
    virtual void set_value(const std::string& v);

public:
    /**
     * @brief Resets string argument.
     */
    virtual void reset();

private:
    std::string m_value;
    std::string m_default_value;

public:
    /**
     * @brief Constructor.
     * @param name Name of string argument.
     * @param default_value Default value.
     */
    cmd_arg_string(std::string name
        , std::string default_value = "");
}; // end of class cmd_arb_string

#endif //CMD_ARG_string_H

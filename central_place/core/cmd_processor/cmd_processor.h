#ifndef CMD_CMD_PROCESSOR_H
#define CMD_CMD_PROCESSOR_H

/**
 * @file cmd_processor.h
 * @brief declaration of class
 *              cmd_processor
 * @author Hayk Khachatryan
 */

#include <string>
#include <map>
#include <vector>

/**
 * @namespace cmd
 * @brief command infrastructure
 *        namespace
 */
namespace cmd
{

class cmd_base;

/**
 * @class cmd_processor
 * @brief Central singleton class
 *        for processing command
 *        line entries.
 */
class cmd_processor
{
    /// @name command management.
    /// @{
public:
    /**
     * @brief Adds command to command list
     *        of command processor.
     * @param cmd Command to add.
     */
    void add_command(cmd_base* cmd);

public:
    /**
     * @brief Parses command string and
     *        makes execution.
     * @param c_l Command string.
     */
    void parse_and_execute_command(const std::string& c_l);

private:
    /**
     * @brief Parses argument list and set to
     *        command.
     * @param cmd Command to set arguments.
     * @param a_l Argument list to set.
     */
    void parse_arg_list(cmd_base* cmd, const std::vector<std::string>& a_l);

private:
    std::map<std::string, cmd_base*> m_commands;
    /// @}

    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static cmd_processor& get_instance();

public:
    /**
     * @brief Intstantiates singletone object.
     */
    static void instantiate();

public:
    /**
     * @brief Destroys singletone object.
     */
    static void destroy();

private:
    static cmd_processor* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    cmd_processor() = default;

public:
    /**
     * @brief Destructor.
     */
    ~cmd_processor();
private:
    cmd_processor(const cmd_processor&) = delete;
    cmd_processor& operator=(const cmd_processor&) = delete;
    /// @}
}; // end of class cmd_processor

} // end of namespace cmd

 #endif //CMD_CMD_PROCESSOR_H

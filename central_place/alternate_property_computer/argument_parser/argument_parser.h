/**
 * @file argument_parser/argument_parser.h
 * @brief declaration of class argument_parser.
 */

#pragma once

#include "types.h"
#include <boost/program_options.hpp>

#include <fstream>

/**
 * @class argument_parser
 * @brief this class is used for parsing argument of program and
 *        converting them to the appropriate types.
 * @note Singleton class.
 */
class argument_parser
{
    /// @name parsing interface
    /// @{
public:
    /**
     * @brief Parses the arguments and returns map of name->value.
     * @param argc Argument cound of the process.
     * @param argv Pointer to the argument list of the process.
     * @param rank_of_process Rank of the current process, for 
     *        secondary processes argument parsing is not needed,
     *        so it will return an empty map.
     */
    arg_name_to_value_map parse_and_get_args(
        int argc, char* argv[], int rank_of_process) const;
private:
    boost::program_options::options_description m_options_description;
    std::ofstream& m_logger;
    /// @}
    
    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static argument_parser& get_instance();

public:
    /**
     * @brief Intstantiates singletone object.
     */
    static void instantiate(std::ofstream& logger);

public:
    /**
     * @brief Destroys singletone object.
     */
    static void destroy();

private:
    static argument_parser* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    argument_parser(std::ofstream& logger);

public:
    /**
     * @brief Destructor.
     */
    ~argument_parser() = default;
private:
    argument_parser(const argument_parser&) = delete;
    argument_parser& operator=(const argument_parser&) = delete;
    /// @}
};

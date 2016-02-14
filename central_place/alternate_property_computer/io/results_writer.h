/**
 * @file io/results_writer.h
 * @brief declaration of results_writer class
 */

#pragma once

#include "types.h"
#include <fstream>
#include "libxl.h"


/**
 * TODO: 1) make base class for writers to
 *          write different kinds of results.
 */

/**
 * @class results_writer
 * @brief writes results
 */
class results_writer
{
public:
    /**
     * @brief Prepares writer.
     * @param n Vertex count of graph
     * @param p Probability of Erdos-Renyi graph
     * @note Must be called only one time.
     */
    void prapare_writer(unsigned n, double p);

private:
    /**
     * @brief Prepares output directory.
     * @return Returns false if praparing faild.
     */
    bool prepare_output_directory();

    void prepare_excel_file();

public:
    /**
     * @brief Writes single result list.
     * @param r Single result list.
     * @param n Vertex count of graph.
     * @param p Probability of Erdos-Renyi graph
     * @param mu Mu of calculation.
     */
    void write_single_results_list(const single_results_list& r, double mu) const;

    /**
    * @brief Writes graph size and probability into the excel file
    */
    void write_graph_info();

    /**
    * @brief Writes Graph item property computation result path into the excel file
    * @param result result vector
    * @param type property type
    */
    template <class T>
    void write_graph_item_property_result(const T& result,
        const PropertyComputerType type);


    /**
    * @brief Add entry in excel file
    * @param file_name name of the result file
    * @param property_name name of the computed property
    */
    void addToSheet(const std::string& file_name,
        const std::string& property_name);

    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static results_writer& get_instance();

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
    static results_writer* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    results_writer(std::ofstream& logger);

public:
    /**
     * @brief Destructor.
     */
    ~results_writer();
private:
    results_writer(const results_writer&) = delete;
    results_writer& operator=(const results_writer&) = delete;
    /// @}

private:
    std::string m_directory_name;
    std::string m_excel_file_name;
    libxl::Book* m_book;
    libxl::Sheet* m_sheet;
    unsigned m_next_row;

    bool m_is_writer_ready;
    unsigned m_vertex_count;
    double m_probability;
    std::ofstream& m_logger;
};

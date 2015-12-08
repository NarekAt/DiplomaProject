#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

namespace converter {

/**
 * @brief Exception while converting.
 */
class exception
{
public:
        /**
         * @brief Gets exception message.
         * @return Exception message.
         */
        const std::string& get_message() const;

private:
        std::string m_message;

public:
        /**
         * @brief Constructor.
         * @param message Exception message.
         */
        exception(const std::string& message);
};

/**
 * @brief Calls appropriate convert function
 *        depending on flag value.
 * @param flag Value of this flag can be:
 *        's' which means convert from standart graph.
 *        'b' which means convert from boost graph.
 * @param f_f_n First file name.
 * @param s_f_n Second file name.
 * @note File name can be or boost graph or standard graph
 *       file name
 * @throw wrong_flag
 * @throw converter::cannot_open_boost_graph_file
 * @throw converter::cannot_open_standart_graph_file
 * @throw converter::problem_on_reading_boost_graph_file
 * @throw converter::problem_on_writing_boost_graph_file
 * @throw converter::wrong_format_of_standart_graph_file
 */
void convert(char flag, const std::string& f_f_n
        , const std::string& s_f_n);

/**
 * @brief Reads boost graph file and writes into
 *        standart graph file.
 * @param b_g_f_n Boost graph file name
 * @param s_g_f_n Standart graph file name
 */
void convert_from_boost_graph(const std::string& b_g_f_n
        , const std::string& s_g_f_n);

/**
 * @brief Reads standart graph file and writes into
 *        boost graph file.
 * @param s_g_f_n Standart graph file name
 * @param b_g_f_n Boost graph file name
 */
void convert_from_standart_graph(const std::string& s_g_f_n
        , const std::string& b_g_f_n);

}

#endif // CONVERTER_H

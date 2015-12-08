#include <iostream>
#include "converter.h"

std::string help("Graph-converter is used for conversation between\nstandart graph file and boost graph file.\nIt has two usages:\n------------------------------\n./graph_converter <flag> <first_file_name> <second_file_name>\n------------------------------\nIf <flag> is 'b', then <first_file_name> must be\nboost graph file name,\n<second_file_name> must be\nstandart graph file name.\n------------------------------\nIf <flage> is 's', then <first_file_name> must be\nstandart graph file name,\n<second_file_name> must be\nboost graph file name\n.");

void print_help()
{
        std::cout << "===============================\n";
        std::cout << help; 
        std::cout << "===============================\n";
}

int main(int argc, char* argv[])
{
        if (1 == argc) {
                print_help();
                return 0;
        }
        if (4 != argc) {
                std::cout << "ERROR: Count of arguments is incorrect." << std::endl;
                print_help();
                return 0;
        }
        try {
                const std::string f1(argv[2]);
                const std::string f2(argv[3]);
                converter::convert(argv[1][0], f1, f2);
        } catch (converter::exception& ex) {
                std::cout << std::string("ERROR: ") 
                          << ex.get_message() << std::endl;
        }
        return 0;
}

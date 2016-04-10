// Description:
//      Boost C++ parser for config file
// Authors: Aram Elchyan, Narek Atayan

// Config file prototype
// <?xml version="1.0"?>
// <config>
//     <graph-path></graph-path>
//     <clusters-count></clusters-count>
//     <properties>
//         <property></property>
//         <property></property>
//         <property></property>
//         <property></property>
//     </properties>
// </config>

#ifndef INCLUDED__CONFIG_FILE_PARSER_H
#define INCLUDED__CONFIG_FILE_PARSER_H

#include "types.h"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>


class CFGParser
{
public:
    typedef std::vector<alternate_property_type> APTList;

    struct Config
    {
        std::string graphFilePath;
        unsigned    clustersCount;
        APTList     aptList;
    };

public:
    static Config parse(const std::string& cfgFilePath);

private:
    CFGParser() = delete;
    CFGParser(const CFGParser& rhs) = delete;
    CFGParser& operator=(const CFGParser& rhs) = delete;
};

#endif

#include "config_file_parser.h"

CFGParser::Config CFGParser::parse(const std::string& cfgFilePath)
{
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(cfgFilePath, pt);

    Config config;
    try
    {
        config.graphFilePath = pt.get<std::string>("config.graph-path");
        config.clustersCount = pt.get<unsigned>("config.clusters-count");

        for (const auto property : pt.get_child("config.properties"))
        {
            const auto type = get_alternate_property_type_by_name(property.second.data());
            config.aptList.push_back(type);
        }
    }
    catch(...)
    {
        throw std::runtime_error("Config file parse error");
    }

    return config;
}

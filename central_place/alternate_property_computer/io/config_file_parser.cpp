#include "config_file_parser.h"

CFGParser::Config CFGParser::parse(const std::string& cfgFilePath)
{
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(cfgFilePath, pt);

    Config config;
    try
    {
        for(const auto path : pt.get_child("config.graphs"))
        {
            config.gpList.push_back(path.second.data());
        }

        for (const auto property : pt.get_child("config.properties"))
        {
            const auto type = get_alternate_property_type_by_name(property.second.data());
            config.aptList.push_back(type);
        }

        config.calculateAvg = pt.get<bool>("config.calculate-average");
        config.calculateDistr = pt.get<bool>("config.calculate-distribution");
    }
    catch(...)
    {
        throw std::runtime_error("Config file parse error");
    }

    return config;
}

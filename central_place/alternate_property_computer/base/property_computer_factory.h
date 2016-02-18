/**
 * @file base/property_computer_factory.h
 * @brief declaration of property_computer_factory class
 */

#ifndef INCLUDED__PROPERTY_COMPUTER_FACTORY_H
#define INCLUDED__PROPERTY_COMPUTER_FACTORY_H

#include "property_computer_base.h"

namespace Base
{

class property_computer_factory
{
public:
    template <class ResType>
    static PropertyComputerBase<ResType>* get_computer(graph_types::graph& graph,
            alternate_property_type t);
};

}
#endif

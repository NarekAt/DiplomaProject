/**
 * @file package/package.cpp
 * @brief definition of package class.
 */

#include "package.h"
#include "coordinator.h"
#include "argument_parser.h"

void package::init(std::ofstream& logger)
{
    argument_parser::instantiate(logger);
    coordinator::instantiate(logger);
}

void package::uninit()
{
    coordinator::destroy();
    argument_parser::destroy();
}

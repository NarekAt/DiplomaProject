/**
 * @file package/package.cpp
 * @brief definition of package class.
 */

#include "package.h"
#include "mediator.h"
#include "argument_parser.h"
#include "results_writer.h"

void package::init(std::ofstream& logger)
{
    argument_parser::instantiate(logger);
    mediator::instantiate(logger);
    results_writer::instantiate(logger);
}

void package::uninit()
{
    results_writer::destroy();
    mediator::destroy();
    argument_parser::destroy();
}

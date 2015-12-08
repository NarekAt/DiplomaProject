/**
 * @file common/types.h
 * @brief common typedefs enums e.t.c
 */

#pragma once

#include <map>
#include <string>
#include <boost/any.hpp>

/**
 * @brief Map of process arguments name to value.
 */
typedef std::map<std::string, boost::any> arg_name_to_value_map;

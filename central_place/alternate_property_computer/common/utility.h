/**
 * @file common/utility.h
 * @brief declarations of utility functions
 */

#pragma once

#include "graph_types.h"

#define MULTIPLE_TYPEDEF2(type, n1, n2) \
    typedef type n1;                    \
    typedef type n2

#define MULTIPLE_TYPEDEF3(type, n1, n2, n3) \
    MULTIPLE_TYPEDEF2(type, n1, n2);        \
    typedef type n3

#define MULTIPLE_TYPEDEF4(type, n1, n2, n3, n4) \
    MULTIPLE_TYPEDEF3(type, n1, n2, n3);        \
    typedef type n4



#define DECLARE_DELEGATING_CTOR0(TypeName, BaseTypeName)  \
        TypeName() : BaseTypeName() {}

#define DECLARE_DELEGATING_CTOR1(TypeName, BaseTypeName)  \
        template<class T1>                                      \
        explicit TypeName(const T1& t1)                         \
            : BaseTypeName(t1) {}

#define DECLARE_DELEGATING_CTOR2(TypeName, BaseTypeName)  \
        template<class T1, class T2>                            \
        TypeName(const T1& t1, const T2& t2)                    \
            : BaseTypeName(t1, t2) {}

#define DECLARE_DELEGATING_CTOR3(TypeName, BaseTypeName)  \
        template<class T1, class T2, class T3>                  \
        TypeName(const T1& t1, const T2& t2, const T3& t3)      \
            : BaseTypeName(t1, t2, t3) {}

#define DECLARE_DELEGATING_CTORS(TypeName, BaseTypeName)  \
    DECLARE_DELEGATING_CTOR0(TypeName, BaseTypeName)      \
    DECLARE_DELEGATING_CTOR1(TypeName, BaseTypeName)      \
    DECLARE_DELEGATING_CTOR2(TypeName, BaseTypeName)      \
    DECLARE_DELEGATING_CTOR3(TypeName, BaseTypeName)      \
    /* end of multi-line macro */


namespace utility
{

/**
 * @brief Returns another vertex of the edge.
 * @param v Initial vertex
 * @param e Edge
 * @return Another vertex of v
 * @pre vertex must be one of the vertices of given edge
 */
graph_types::vertex get_another_vertex(graph_types::vertex v, graph_types::edge e);

}

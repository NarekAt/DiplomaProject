#ifndef INCLUDED__SHORTEST_PATH_H
#define INCLUDED__SHORTEST_PATH_H

#include "property_computer_base.h"
#include "utility.h"

#include "shortestpath_base.h"

#include <vector>

namespace Base
{

class ShortestPath : public PropertyComputerBase<std::vector<unsigned> >
{
public:
    typedef PropertyComputerBase<std::vector<unsigned> > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(ShortestPath, BaseType);

protected:
    virtual void computeImpl();

    virtual PropertyComputerType typeImpl() const;

    virtual ResultType getDistributionImpl() const;
};

} // namespace Base

#endif

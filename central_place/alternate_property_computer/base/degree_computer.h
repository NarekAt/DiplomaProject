#ifndef INCLUDED__DEGREE_COMPUTER_HPP
#define INCLUDED__DEGREE_COMPUTER_HPP

#include "property_computer_base.h"
#include "utility.h"

#include <vector>

namespace Base
{

class DegreeComputer : public PropertyComputerBase<std::vector<unsigned> >
{
public:
    typedef PropertyComputerBase<std::vector<unsigned> > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(DegreeComputer, BaseType);

protected:
    virtual void computeImpl();

    virtual PropertyComputerType typeImpl() const;

    virtual ResultType getDistributionImpl() const;
};

}
#endif

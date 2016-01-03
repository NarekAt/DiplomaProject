#ifndef INCLUDED__BETWEENNESS_CENTRALITY_HPP
#define INCLUDED__BETWEENNESS_CENTRALITY_HPP

#include "property_computer_base.h"
#include "utility.h"

#include <vector>

namespace Base
{

class BC : public PropertyComputerBase<std::vector<double> >
{
public:
    typedef PropertyComputerBase<std::vector<double> > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(BC, BaseType);

protected:
    virtual void computeImpl();

    virtual PropertyComputerType typeImpl() const;

    virtual ResultType getDistributionImpl() const;
};

}
#endif

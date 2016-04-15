#ifndef INCLUDED__EIGENVECTOR_CENTRALITY_HPP
#define INCLUDED__EIGENVECTOR_CENTRALITY_HPP

#include "property_computer_base.h"
#include "utility.h"

#include <vector>

namespace Base
{

class EVC : public PropertyComputerBase<std::vector<double>>
{
public:
    typedef PropertyComputerBase<std::vector<double> > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(EVC, BaseType);

protected:
    virtual void computeImpl();

    virtual alternate_property_type typeImpl() const;

    virtual ResultType getDistributionImpl() const;
};

} // namespace Base

#endif

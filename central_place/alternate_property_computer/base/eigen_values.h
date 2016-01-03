#ifndef INCLUDED__EIGEN_VALUES_H
#define INCLUDED__EIGEN_VALUES_H

#include "property_computer_base.h"
#include "utility.h"

#include <vector>
#include <complex>

namespace Base
{

class EigenValues : public PropertyComputerBase<std::vector<std::complex<double> > >
{
public:
    typedef PropertyComputerBase<std::vector<std::complex<double> > > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(EigenValues, BaseType);

protected:
    virtual void computeImpl();

    virtual PropertyComputerType typeImpl() const;

    virtual ResultType getDistributionImpl() const;
};

}
#endif

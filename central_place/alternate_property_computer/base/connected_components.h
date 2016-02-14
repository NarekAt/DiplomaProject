//////////////////////////////////////////////////////////
//      Description:                                    //
//          Parallel multithreaded version of           //
//          Shiloach-Vishkin algorithm for finding      //
//          the connected components of a graph.        //
//////////////////////////////////////////////////////////

#ifndef INCLUDED__CONNECTED_COMPONENTS_H
#define INCLUDED__CONNECTED_COMPONENTS_H

#include "property_computer_base.h"
#include "utility.h"

#include <vector>

#include <mutex>

namespace Base
{

class ConnectedComponents :
    public PropertyComputerBase<std::vector<unsigned> >
{
public:
    typedef PropertyComputerBase<std::vector<unsigned> > BaseType;
    typedef BaseType::ResultType ResultType;

    DECLARE_DELEGATING_CTOR1(ConnectedComponents, BaseType);

protected:
    virtual void computeImpl();

    virtual PropertyComputerType typeImpl() const;

    virtual ResultType getDistributionImpl() const;

private:
    std::mutex mutex_;
};

} // namespace Base

#endif

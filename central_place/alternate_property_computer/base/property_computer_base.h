/**
 * @file base/property_computer_base.h
 * @brief declaration of property_computer class.
 */

#ifndef INCLUDED__PROPERTY_COMPUTER_BASE_H
#define INCLUDED__PROPERTY_COMPUTER_BASE_H

#include "graph.h"
#include "types.h"

namespace Base
{

template <class T>
class PropertyComputerBase
{
public: // types
    typedef T ResultType;

public: // functions
    PropertyComputerBase(const graph_types::graph& g)
        : graph_(g)
        , results_(g.size())
    {}

    void compute()
    {
        if (results_.empty())
            return;

        computeImpl();
    }

    ResultType getResult() const
    {
        return results_;
    }

    alternate_property_type type() const
    {
        return typeImpl();
    }

public:
    ResultType getDistribution() const
    {
        return getDistributionImpl();
    }

private: // virtual impl functions
    virtual void computeImpl() = 0;
    virtual alternate_property_type typeImpl() const = 0;
    virtual ResultType getDistributionImpl() const = 0;

protected: // data
    const graph_types::graph& graph_;
    ResultType results_;

private: // non-copyable
    PropertyComputerBase(const PropertyComputerBase&) = delete;
    PropertyComputerBase& operator=(const PropertyComputerBase&) = delete;
};

} // namespace Base
#endif

/**
 * @file base/property_computer_factory.h
 * @brief declaration of property_computer_factory class
 */

#ifndef INCLUDED__PROPERTY_COMPUTER_FACTORY_H
#define INCLUDED__PROPERTY_COMPUTER_FACTORY_H

#include <memory>
#include "mediator.h"

namespace Base
{

class Holder
{
public:
    virtual ~Holder() {}

    virtual void compute() = 0;
    virtual void writeResults() const = 0;
    virtual void writeDitribution() const = 0;

};

template <typename T>
class HolderT: public Holder
{
public:
     HolderT(graph_types::graph& g)
         : _t(g)
     {}

     virtual void compute()
     {
         _t.compute();
     }

     virtual void writeResults() const
     {
         mediator::get_instance().write_results(_t.getResult(), _t.type());
     }

     virtual void writeDitribution() const
     {
         try
         {
            const auto& res = _t.getDistribution();
            mediator::get_instance().write_distribution(res, _t.type());
         }
         catch (const std::exception& e)
         {
             std::cout << e.what() << std::endl;
             std::cout << "Skipping..." << std::endl;
         }
     }

private:
    T _t;
};

using maker = std::unique_ptr<Holder> (*)(graph_types::graph& g);
using maker_map = std::map<alternate_property_type, maker>;

template <typename T>
std::unique_ptr<Holder>
make_holder(graph_types::graph& g)
{
    return std::unique_ptr<Holder>(new HolderT<T>(g));
}

class PropertyComputerController
{
public:
    PropertyComputerController() = default;

    static PropertyComputerController& getInstance()
    {
        static PropertyComputerController instance;
        return instance;
    }

    void registerPropertyComputers(); 

    std::unique_ptr<Holder>
    createPropertyComputer(alternate_property_type const E, graph_types::graph& g);

private:
    PropertyComputerController(const PropertyComputerController&) = delete;
    PropertyComputerController& operator=(const PropertyComputerController&) = delete;

private:
    maker_map mm;
};

class PropertyComputerRunner
{
public:
    static void compute_and_write(graph_types::graph& g,
                                  alternate_property_type const p);

    static void calculate_distributions_and_write(graph_types::graph& g,
                                  alternate_property_type const p);
};

}
#endif

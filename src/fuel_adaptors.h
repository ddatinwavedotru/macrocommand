#ifndef FUEL_ADAPTORS_H
#define FUEL_ADAPTORS_H

#include <memory>
#include "interfaces.h"
#include "fuel_interfaces.h"

class BurningFuelObjectAdapter: public IBurningFuelObject {

public:
    static const char * fuelAmount_key;
    static const char * fuelConsuption_key;

    BurningFuelObjectAdapter(const std::shared_ptr<IGameItem> & item): m_item(item) {}

    FuelAmount fuelAmount() const override { return get<FuelAmount>(*m_item,fuelAmount_key); }
    FuelAmount fuelConsumption() const override { return get<FuelAmount>(*m_item,fuelConsuption_key) ;}
    void set_fuelAmount(FuelAmount const & f) override { return m_item->set(fuelAmount_key,f); }
protected:
    std::shared_ptr<IGameItem> m_item;
};

class ObjectThatCanHaveFuelAdaptor: public IObjectThatCanHaveFuel {
public:
    ObjectThatCanHaveFuelAdaptor(const std::shared_ptr<IGameItem> & item): m_item(item) {}
    bool hasEnoughFuel() const override { return get<FuelAmount>(*m_item,BurningFuelObjectAdapter::fuelAmount_key) > 0; }
protected:
    std::shared_ptr<IGameItem> m_item;
};




#endif // FUEL_ADAPTORS_H

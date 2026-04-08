#ifndef FUEL_INTERFACES_H
#define FUEL_INTERFACES_H

class IObjectThatCanHaveFuel {
public:
    virtual ~IObjectThatCanHaveFuel(){}
    virtual bool hasEnoughFuel() const=0;
};

using FuelAmount=unsigned;

class IBurningFuelObject {
public:
    virtual ~IBurningFuelObject() {}
    virtual FuelAmount fuelAmount() const=0;
    virtual FuelAmount fuelConsumption() const=0;
    virtual void set_fuelAmount(FuelAmount const & f)=0;

};

#endif // FUEL_INTERFACES_H

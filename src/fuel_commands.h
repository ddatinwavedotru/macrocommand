#ifndef FUEL_COMMANDS_H
#define FUEL_COMMANDS_H

#include <iomanip>
#include "commands.h"
#include "fuel_interfaces.h"

class CheckFuelCommand: public ICommand {
public:
    CheckFuelCommand(std::shared_ptr<const IObjectThatCanHaveFuel> const & o): m_o(o) {}

    void execute() override {
        if(!m_o->hasEnoughFuel()) {
            throw std::runtime_error("does not have enough fuel");
        }
    }
protected:
    std::shared_ptr<const IObjectThatCanHaveFuel> m_o;
};

class BurnFuelCommand: public ICommand {
public:
    BurnFuelCommand(std::shared_ptr<IBurningFuelObject> const & o): m_o(o) {}

    void execute() override {
        m_o->set_fuelAmount(m_o->fuelAmount()-m_o->fuelConsumption());
    }

protected:
   std::shared_ptr<IBurningFuelObject> m_o;
};

class LoggingCommand: public ICommand {
public:
    LoggingCommand(std::ostream & oss):m_oss(oss) {}
    void log(std::string const & s) { m_oss<<s<<std::endl; }
protected:
    std::ostream & m_oss;
};

class LoggingSomethingCommand: public LoggingCommand {
public:
    LoggingSomethingCommand(std::ostream & oss): LoggingCommand(oss) {}
    void execute() override { this->log("something"); }

};

class ThrowingCommand: public ICommand {
public:
    ThrowingCommand() {}
    void execute() override { throw std::runtime_error("Error occured during command execution."); }
};

#endif // FUEL_COMMANDS_H

#ifndef INTERFACES_H
#define INTERFACES_H

#include <any>
#include <optional>
#include <string>

#include "datatypes.h"

class ICommand {
public:
    virtual ~ICommand(){}
    virtual void execute() =0;
};

class IMovingObject {
public:
    virtual ~IMovingObject(){}
    virtual Point location() const =0;
    virtual Vector velocity() const =0;
    virtual void set_location(Point const & p)=0;

};

class IVelocityAccessObject {
public:
    virtual ~IVelocityAccessObject(){}
    virtual Vector velocity() const =0;
    virtual void set_velocity(Vector const & v)=0;
    virtual bool hasVelocity() const =0;
};

class IRotatingObject {
public:
    virtual ~IRotatingObject(){}
    virtual Angle angle() const =0;
    virtual Angle angularVelocity() const =0;
    virtual void set_angle(Angle const & a)=0;
};

class IGameItem {
public:
    virtual ~IGameItem(){}
    virtual std::optional<std::any> get(std::string const &key) const =0;
    virtual void set(std::string const &key, std::any value)=0;
};

template<typename T>
inline T get(IGameItem const & it, std::string const & key) {
    std::optional<std::any> opt=it.get(key);
    if(!opt) {
        return T();
    }
    return std::any_cast<T>(opt.value());
}

#endif // INTERFACES_H

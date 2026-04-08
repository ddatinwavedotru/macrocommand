#ifndef ADAPTORS_H
#define ADAPTORS_H

#include <stdexcept>
#include <memory>
#include "interfaces.h"


class MovingObjectAdapter: public IMovingObject {
public:

    static const char * location_key;
    static const char * velocity_key;

    MovingObjectAdapter(const std::shared_ptr<IGameItem> & item):m_item(item) {}

    Point location() const override { return get<Point>(*m_item, location_key); }
    Vector velocity() const override { return get<Vector>(*m_item, velocity_key); }
    void set_location(Point const & p) override { m_item->set(location_key,p); }

protected:
    std::shared_ptr<IGameItem> m_item;
};

class VelocityAccessObjectAdapter: public IVelocityAccessObject {
public:
    VelocityAccessObjectAdapter(const std::shared_ptr<IGameItem> & item):m_item(item) {}

    Vector velocity() const override { return get<Vector>(*m_item, MovingObjectAdapter::velocity_key); }
    void set_velocity(Vector const & p) override { m_item->set(MovingObjectAdapter::velocity_key,p); }
    bool hasVelocity() const override { return m_item->get(MovingObjectAdapter::velocity_key).has_value(); }

protected:
    std::shared_ptr<IGameItem> m_item;
};


class RotatingObjectAdapter: public IRotatingObject {
public:

    static const char * angle_key;
    static const char * angularVelocity_key;

    RotatingObjectAdapter(const std::shared_ptr<IGameItem> & item): m_item(item) {}

    Angle angle() const override { return get<Angle>(*m_item,angle_key); }
    Angle angularVelocity() const override { return get<Angle>(*m_item,angularVelocity_key) ;}
    void set_angle(Angle const & a) override { return m_item->set(angle_key,a); }
protected:
    std::shared_ptr<IGameItem> m_item;
};

class UnreadableLocationAdapter: public MovingObjectAdapter {
    using Super_type=MovingObjectAdapter;
public:
    UnreadableLocationAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    Point location() const override {
        auto loc=m_item->get(location_key);
        return std::any_cast<Point>(loc.value());
    }
};

class UnreadableVelocityAdapter: public MovingObjectAdapter {
    using Super_type=MovingObjectAdapter;
public:
    UnreadableVelocityAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    Vector velocity() const override {
        auto loc=m_item->get(velocity_key);
        return std::any_cast<Vector>(loc.value());
    }
};

class FixedPositionObjectAdapter: public MovingObjectAdapter {
    using Super_type=MovingObjectAdapter;
public:
    FixedPositionObjectAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    void set_location(Point const & loc) override { throw std::runtime_error("the object is fixed"); }
};



class UnreadableAngleAdapter: public RotatingObjectAdapter {
    using Super_type=RotatingObjectAdapter;
public:
    UnreadableAngleAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    Angle angle() const override {
        auto loc=m_item->get(angle_key);
        return std::any_cast<Angle>(loc.value());
    }
};

class UnreadableAngularVelocityAdapter: public RotatingObjectAdapter {
    using Super_type=RotatingObjectAdapter;
public:
    UnreadableAngularVelocityAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    Angle angularVelocity() const override {
        auto loc=m_item->get(angularVelocity_key);
        return std::any_cast<Angle>(loc.value());
    }
};

class FixedAngleObjectAdapter: public RotatingObjectAdapter {
    using Super_type=RotatingObjectAdapter;
public:
    FixedAngleObjectAdapter(const std::shared_ptr<IGameItem> & item): Super_type(item) {}

    void set_angle(Angle const & loc) override { throw std::runtime_error("the object's angle is fixed"); }
};

#endif // ADAPTORS_H

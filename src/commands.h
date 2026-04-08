#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>

#include "interfaces.h"

class Move: public ICommand {
public:
    Move(std::shared_ptr<IMovingObject> const & o) : m_o(o) {}

    void execute() override {
        Point location=m_o->location();
        Vector velocity=m_o->velocity();
        location+=velocity;
        m_o->set_location(location);
    }

protected:
    std::shared_ptr<IMovingObject> m_o;
};

class Rotate: public ICommand {
public:
    Rotate(std::shared_ptr<IRotatingObject> const & o) : m_o(o) {}

    void execute() override {
        m_o->set_angle(m_o->angle()+m_o->angularVelocity());
    }

protected:
    std::shared_ptr<IRotatingObject> m_o;
};

// Реализовать команду для модификации вектора мгновенной скорости при повороте. Необходимо учесть, что не каждый разворачивающийся объект движется.
class ChangeVelocityCommand: public ICommand {
public:
    ChangeVelocityCommand(std::shared_ptr<IRotatingObject> const & ro, std::shared_ptr<IVelocityAccessObject> const & vao): m_ro(ro), m_vao(vao){}

    void execute() override {
        if(m_vao->hasVelocity()) {
            Vector vel=m_vao->velocity();
            double velAbs=std::hypot(vel.x(),vel.y());
            if(velAbs>0) {
                Angle angle=m_ro->angle();
                vel=Vector(velAbs*std::cos(angle),velAbs*std::sin(angle));
                m_vao->set_velocity(vel);
            }
        }
    }

protected:
    std::shared_ptr<IRotatingObject> m_ro;
    std::shared_ptr<IVelocityAccessObject> m_vao;
};

class CommandException: public std::runtime_error {
public:
    CommandException(std::string const & text): std::runtime_error(text) {}
};


class MacroCommand: public ICommand {
public:
    MacroCommand() {}
    MacroCommand(std::vector<std::shared_ptr<ICommand> > const & commands): m_commands(commands) {}
    void execute() override {
        try {
            for(auto const & p:m_commands) {
                if(p) {
                    p->execute();
                }
            }
        } catch(std::exception const & ex) {
            throw CommandException(ex.what());
        }
    }
    MacroCommand & operator<<(std::shared_ptr<ICommand> const & cmd) { m_commands.push_back(cmd); return *this; }
public:
    std::vector<std::shared_ptr<ICommand> > m_commands;
};


#endif // COMMANDS_H

#pragma once
#include <man/componentstorage.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t {
    virtual ~GameContext_t() = default;
    virtual const Vec_t<Entity_t>& getEntities() const = 0;
    virtual       Vec_t<Entity_t>& getEntities()       = 0;
    virtual const std::vector<PhysicsComponent_t>& getPhysicsComponents() const = 0;
    virtual       std::vector<PhysicsComponent_t>& getPhysicsComponents()       = 0;
};


} // namespace ECS
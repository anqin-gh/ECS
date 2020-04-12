#pragma once
#include <cmp/entity.hpp>
#include <cmp/physics.hpp>
#include <cmp/render.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t {
    virtual ~GameContext_t() = default;

    virtual const Vec_t<Entity_t>& getEntities() const = 0;
    virtual       Vec_t<Entity_t>& getEntities()       = 0;

    virtual const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const = 0;
    virtual       Vec_t<PhysicsComponent_t>& getPhysicsComponents()       = 0;

    virtual const Vec_t<RenderComponent_t>&  getRenderComponents() const = 0;
    virtual       Vec_t<RenderComponent_t>&  getRenderComponents()       = 0;

    virtual const PhysicsComponent_t* getRequiredPhysicsComponentByEntityID(EntityID_t eid) const = 0;
    virtual       PhysicsComponent_t* getRequiredPhysicsComponentByEntityID(EntityID_t eid)       = 0;
};


} // namespace ECS
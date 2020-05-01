#pragma once
#include <cstdint>

#include <ecs/cmp/component.hpp>

struct PhysicsComponent_t : public ECS::ComponentBase_t<PhysicsComponent_t> {
    explicit PhysicsComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {}

    uint32_t  x{0},  y{0};
    int32_t  vx{0}, vy{0};
};

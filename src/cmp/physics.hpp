#pragma once
#include <iostream>
#include <cstdint>

#include <cmp/component.hpp>

namespace ECS {

struct PhysicsComponent_t : public Component_t {
    explicit PhysicsComponent_t(EntityID_t eid)
        : Component_t(eid)
    {}

    uint32_t  x{0},  y{0};
    int32_t  vx{1}, vy{1};
};

} // namespace ECS

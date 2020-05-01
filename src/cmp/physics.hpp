#pragma once
#include <cstdint>

#include <cmp/component.hpp>

namespace ECS {

struct PhysicsComponent_t : public Component_t {
    explicit PhysicsComponent_t(EntityID_t eid)
        : Component_t(eid)
    {}

    uint32_t  x{0},  y{0};
    int32_t  vx{0}, vy{0};
};

} // namespace ECS

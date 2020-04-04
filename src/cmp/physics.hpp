#pragma once
#include <iostream>
#include <cstdint>

namespace ECS {

struct PhysicsComponent_t {
    explicit PhysicsComponent_t() = default;

    uint32_t  x{0},  y{0};
    int32_t  vx{1}, vy{1};
};

} // namespace ECS

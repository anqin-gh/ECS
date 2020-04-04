#pragma once

#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t;

struct PhysicsSystem_t {
    explicit PhysicsSystem_t() = default;
    bool update(GameContext_t& context) const;
};

} // namespace ECS

#pragma once

#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t;

struct CollisionSystem_t {
    explicit CollisionSystem_t() = default;
    bool update(GameContext_t& context) const;
};

} // namespace ECS

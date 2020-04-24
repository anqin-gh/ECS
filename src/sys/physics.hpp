#pragma once
#include <cmp/physics.hpp>
#include <util/typealiases.hpp>

namespace ECS {

template<typename GameCTX_t>
struct PhysicsSystem_t {
    explicit PhysicsSystem_t() = default;

    bool update(GameCTX_t& ctx) const {
        for(auto& phy : ctx.template getComponents<PhysicsComponent_t>()) {
            phy.x += phy.vx;
            phy.y += phy.vy;
        }
        return true;
    }
};

} // namespace ECS

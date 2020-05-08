#pragma once
#include <game/cmp/physics.hpp>
#include "physics.hpp"

template<typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    for(auto& phy : ctx.template getComponents<PhysicsComponent_t>()) {
        phy.x += phy.vx;
        phy.y += phy.vy;
    }
}

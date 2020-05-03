#pragma once
#include <game/cmp/physics.hpp>
#include "physics.hpp"

template<typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    for(auto& phy : ctx.template getComponents<PhysicsComponent_t>()) {
        phy.x += phy.vx;
        phy.y += phy.vy;
    }
    return true;
}

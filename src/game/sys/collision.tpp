#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/physics.hpp>
#include "collision.hpp"

template<typename GameCTX_t>
CollisionSystem_t<GameCTX_t>::CollisionSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
{}

template<typename GameCTX_t>
bool CollisionSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    for(auto& col : ctx.template getComponents<ColliderComponent_t>()) {
        if (auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(col)) {

            // Convert to screen coordinates
            auto xl{phy->x + col.box.x_left};
            auto xr{phy->x + col.box.x_right};
            auto yu{phy->y + col.box.y_up};
            auto yd{phy->y + col.box.y_down};

            // Detect collisions
            if (xl > m_w || xr > m_w) { phy->x -= phy->vx; phy->vx = -phy->vx; }
            if (yu > m_h || yd > m_h) { phy->y -= phy->vy; phy->vy = -phy->vy; }
        }
    }
    return true;
}

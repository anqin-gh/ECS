#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/debug.hpp>
#include <game/cmp/physics.hpp>
#include "debug.hpp"

template<typename GameCTX_t>
void
DebugSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    for (auto& dbg : ctx.template getComponents<DebugComponent_t>()) {
        auto* col = ctx.template getRequiredComponent<ColliderComponent_t>(dbg);
        auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(dbg);
        if (col && phy) {
            // Convert to screen coordinates
            auto xl { phy->x + col->box.x_left };
            auto xr { phy->x + col->box.x_right };
            auto yu { phy->y + col->box.y_up };
            auto yd { phy->y + col->box.y_down };

            drawHorizontalLine(xl, xr, yu, dbg.color);
            drawHorizontalLine(xl, xr, yd, dbg.color);

        }
    }
}

#include <iostream>
template<typename GameCTX_t>
constexpr void DebugSystem_t<GameCTX_t>::drawHorizontalLine(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color) const noexcept {
    std::cout << "Drawing line {" << x1 << ", " << x2 << "} at y = " << y << "\n";
}

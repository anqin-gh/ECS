#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/health.hpp>
#include <game/sys/health.hpp>

#include <iostream>
using namespace std;

template<typename GameCTX_t>
constexpr void
HealthSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    for (auto& h : ctx.template getComponents<HealthComponent_t>()) {
        if (const auto* col = ctx.template getRequiredComponent<ColliderComponent_t>(h)) {
            if (h.health && hasLeafNodeColided(col->box)) {
                if (--h.health == 0)
                    ctx.markEntityIDToBeDestroyed(h.getBelongingEntityID());
            }
        }
    }
}

template<typename GameCTX_t>
constexpr bool
HealthSystem_t<GameCTX_t>::hasLeafNodeColided(const BoundingBoxNode_t& box_node) const noexcept {
    // TODO: Use approach where inner boxes are true only when outer boxes are. Current approch is the other way round (less efficient)!!!
    if (box_node.children.empty()) {
        return box_node.collided;
    }
    for (const auto& child : box_node.children) {
        if ( hasLeafNodeColided(child) ) return true;
    }
    return false;
}
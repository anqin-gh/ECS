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
            // cout << "Health[EID: " << h.getBelongingEntityID() << ", CID: " << h.getID() << "] = " << h.health << endl;
            if (h.health && hasLeafNodeColided(col->box)) {
                cout << "Remaining life of Entity[" << h.getBelongingEntityID() << "] = " << h.health -1<< endl;
                if (--h.health == 0)
                    ctx.destroyEntityByID(h.getBelongingEntityID());
            }
        }
    }
}

template<typename GameCTX_t>
constexpr bool
HealthSystem_t<GameCTX_t>::hasLeafNodeColided(const BoundingBoxNode_t& box_node) const noexcept {
    if (box_node.children.empty()) return box_node.collided;
    if (box_node.collided) {
        for (const auto& child : box_node.children)
            return hasLeafNodeColided(child);
    }
    return false;
}
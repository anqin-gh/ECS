#pragma once
#include <cmp/physics.hpp>
#include <cmp/render.hpp>

namespace ECS {

template<typename GameCTX_t>
struct CollisionSystem_t {
    explicit CollisionSystem_t() = default;

    bool update(GameCTX_t& ctx) const {
        for(auto& e : ctx.template getEntities()) {
            auto* phy = e.template getComponent<PhysicsComponent_t>();
            auto* ren = e.template getComponent<RenderComponent_t>();
            if(phy && ren) {
                if(phy->x > 640 || phy->x + ren->w > 640) {
                    phy->x -= phy->vx;
                    phy->vx = -phy->vx;
                }
                if(phy->y > 360 || phy->y + ren->h > 360) {
                    phy->y -= phy->vy;
                    phy->vy = -phy->vy;
                }
            }
        }
        return true;
    }

};

} // namespace ECS

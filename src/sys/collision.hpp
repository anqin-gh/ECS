#pragma once
#include <cmp/physics.hpp>
#include <cmp/render.hpp>

namespace ECS {

template<typename GameCTX_t>
struct CollisionSystem_t {
    explicit CollisionSystem_t() = default;

    bool update(GameCTX_t& ctx) const {
        for(auto& e : ctx.template getEntities()) {
            if(e.phy && e.ren) {
                if(e.phy->x > 640 || e.phy->x + e.ren->w > 640) {
                    e.phy->x -= e.phy->vx;
                    e.phy->vx = -e.phy->vx;
                }
                if(e.phy->y > 360 || e.phy->y + e.ren->h > 360) {
                    e.phy->y -= e.phy->vy;
                    e.phy->vy = -e.phy->vy;
                }
            }
        }
        return true;
    }

};

} // namespace ECS

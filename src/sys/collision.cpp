#include <sys/collision.hpp>
#include <util/gamecontext.hpp>

namespace ECS {

bool CollisionSystem_t::update(GameContext_t& context) const {
    for(auto& e : context.getEntities()) {
        if(e.phy) {
            if(e.phy->x > 640 || e.phy->x + e.w > 640) {
                e.phy->x -= e.phy->vx;
                e.phy->vx = -e.phy->vx;
            }
            if(e.phy->y > 360 || e.phy->y + e.h > 360) {
                e.phy->y -= e.phy->vy;
                e.phy->vy = -e.phy->vy;
            }
        }
    }
    return true;
}

} // namespace ECS

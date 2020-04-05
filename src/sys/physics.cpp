#include <cmp/physics.hpp>
#include <sys/physics.hpp>
#include <util/gamecontext.hpp>

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& context) const {
    for(auto& phy : context.getPhysicsComponents()) {
        phy.x += phy.vx;
        phy.y += phy.vy;
    }
    return true;
}

} // namespace ECS

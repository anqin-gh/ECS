#include <sys/physics.hpp>
#include <util/gamecontext.hpp>

namespace ECS {

bool PhysicsSystem_t::update(GameContext_t& context) const {
    for(auto& e : context.getEntities()) {
        e.x += e.vx;
        e.y += e.vy;
    }
    return true;
}

} // namespace ECS

#include <cmp/physics.hpp>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

    auto& e   = m_entities.emplace_back();

    auto& ph  = m_components.createPhysicsComponent(e.getID());
    e.phy = &ph;
    e.phy->x = x; e.phy->y = y;

    auto& rn = m_components.createRenderComponent(e.getID());
    rn.loadFromFile(filename);
    e.ren = &rn;
}

const PhysicsComponent_t*
}

} // namespace ECS

#include <algorithm>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

void EntityManager_t::createEntity(uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = m_entities.emplace_back();

    auto& ph  = m_components.createPhysicsComponent(e.getID());
    e.phy = &ph;
    e.phy->x = x; e.phy->y = y;

    auto& rn = m_components.createRenderComponent(e.getID());
    rn.loadFromFile(filename);
    e.ren = &rn;
}

const PhysicsComponent_t*
EntityManager_t::getRequiredPhysicsComponentByEntityID(EntityID_t eid) const {
    auto found = std::find_if(begin(m_components.getPhysicsComponents()), end(m_components.getPhysicsComponents()), [&](const auto& cmp) {
        return cmp.getBelongingEntityID() == eid;
    });

    if(found != end(m_components.getPhysicsComponents()))
        return &(*found);
    return nullptr;
}

PhysicsComponent_t*
EntityManager_t::getRequiredPhysicsComponentByEntityID(EntityID_t eid) {
    auto ph = const_cast<const EntityManager_t*>(this)->getRequiredPhysicsComponentByEntityID(eid);
    return const_cast<PhysicsComponent_t*>(ph);
}

} // namespace ECS

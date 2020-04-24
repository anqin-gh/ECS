#include <algorithm>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

Entity_t& EntityManager_t::createEntity(uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = m_entities.emplace_back();

    auto& ph  = m_components.createComponent<PhysicsComponent_t>(e.getID());
    e.phy = &ph;
    e.phy->x = x; e.phy->y = y;

    auto& rn = m_components.createComponent<RenderComponent_t>(e.getID());
    rn.loadFromFile(filename);
    e.ren = &rn;

    return e;
}

void EntityManager_t::addInputComponent(Entity_t& e) {
    if(!e.inp) {
        auto& inp = m_components.createComponent<InputComponent_t>( e.getID() );
        e.inp = &inp;
    }
}

const Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) const {
    auto found = std::find_if(begin(m_entities), end(m_entities), [&](const auto& e) {
        return e.getID() == eid;
    });

    if(found != end(m_entities))
        return found.base();
    return nullptr;
}

Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) {
    auto e = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);
    return const_cast<Entity_t*>(e);
}

} // namespace ECS

#include <algorithm>
#include "entitymanager.hpp"

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

template<typename CMP_t>
CMP_t& EntityManager_t::addComponent(Entity_t& e) {
    auto* eCmp = e.getComponent<CMP_t>();
    if (eCmp) return *eCmp;

    // Create component if it doesn't exist
    auto& cmp = m_components.createComponent<CMP_t>( e.getID() );
    e.addComponent(cmp);
    return cmp;
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

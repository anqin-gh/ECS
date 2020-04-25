#include <algorithm>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
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

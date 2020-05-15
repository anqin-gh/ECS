#pragma once
#include <algorithm>
#include <iostream>
#include <ecs/cmp/entity.hpp>
#include "entitymanager.hpp"

namespace ECS {

inline EntityManager_t::EntityManager_t() {
	m_entities.reserve(kNUM_INITIAL_ENTITIES);
	m_to_be_destroyed.reserve(kNUM_INITIAL_ENTITIES);
}

inline Entity_t&
EntityManager_t::createEntity() { return m_entities.emplace_back(); }

inline const Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) const noexcept {
    auto found = std::find_if(begin(m_entities), end(m_entities), [&](const auto& e) {
        return e.getID() == eid;
    });

    if(found != end(m_entities))
        return found.base();
    return nullptr;
}

inline Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) noexcept {
    auto e = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);
    return const_cast<Entity_t*>(e);
}

template<typename CMP_t>
CMP_t&
EntityManager_t::addComponent(Entity_t& e) {
    // Return component if it already exists
    if (auto* cmp = m_components.template getComponentByEntityID<CMP_t>(e.getID()))
        return *cmp;

    // Create component if it doesn't exist
    auto& cmp = m_components.template createComponent<CMP_t>( e.getID() );
    e.addBelongingComponent(cmp);
    return cmp;
}

template<typename CMP_t>
const Vec_t<CMP_t>& 
EntityManager_t::getComponents() const noexcept { return m_components.template getComponents<CMP_t>(); }

template<typename CMP_t>
Vec_t<CMP_t>&
EntityManager_t::getComponents() noexcept { return m_components.template getComponents<CMP_t>(); }

template<typename CMP_t>
const CMP_t*
EntityManager_t::getComponentByEntityID(EntityID_t eid) const noexcept { return m_components.template getComponentByEntityID<CMP_t>(eid); }

template<typename CMP_t>
CMP_t*
EntityManager_t::getComponentByEntityID(EntityID_t eid) noexcept { return m_components.template getComponentByEntityID<CMP_t>(eid); }

template <typename ReqCMP_t, typename CMP_t>
const ReqCMP_t* 
EntityManager_t::getRequiredComponent(const CMP_t& cmp) const noexcept {
    if (auto* e = getEntityByID(cmp.getBelongingEntityID()))
        return m_components.template getComponentByEntityID<ReqCMP_t>(e->getID());
    return nullptr;
}

template <typename ReqCMP_t, typename CMP_t>
ReqCMP_t*
EntityManager_t::getRequiredComponent(const CMP_t& cmp) noexcept {
    auto reqCmp = const_cast<const EntityManager_t*>(this)->getRequiredComponent<ReqCMP_t>(cmp);
    return const_cast<ReqCMP_t*>(reqCmp);
}

inline void
EntityManager_t::markEntityIDToBeDestroyed(EntityID_t eid) {
    m_to_be_destroyed.emplace_back(eid);
}

inline void
EntityManager_t::destroyEntities() {
    for (auto eid : m_to_be_destroyed)
        destroyEntityByID(eid);
    m_to_be_destroyed.clear();
}

inline void
EntityManager_t::destroyEntityByID(EntityID_t eid) {
    std::cout << "Entity[" << eid << "] is dead!\n";
    if (auto* entity = getEntityByID(eid)) {
        for (auto& [ typeID, _ ] : *entity) {
            m_components.deleteComponentByTypeIDAndEntityID(typeID, eid);
        }

        auto found = std::find_if(begin(m_entities), end(m_entities), [eid](const Entity_t& e) {
            return e.getID() == eid;
        });

        if (found != end(m_entities)) {   // TODO: Error management!!!
            *found = m_entities.back();
            m_entities.pop_back();
        }
    }
}

} // namespace ECS

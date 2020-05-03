#pragma once
#include <algorithm>
#include <ecs/cmp/entity.hpp>
#include "entitymanager.hpp"

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

Entity_t&
EntityManager_t::createEntity() { return m_entities.emplace_back(); }

const Vec_t<Entity_t>&
EntityManager_t::getEntities() const noexcept { return m_entities; }

Vec_t<Entity_t>&
EntityManager_t::getEntities() noexcept { return m_entities; }


template<typename CMP_t>
const Vec_t<CMP_t>&
EntityManager_t::getComponents() const { return m_components.getComponents<CMP_t>(); }

template<typename CMP_t>
Vec_t<CMP_t>&
EntityManager_t::getComponents() { return m_components.getComponents<CMP_t>(); }

template<typename CMP_t>
CMP_t& EntityManager_t::addComponent(Entity_t& e) {
    auto* eCmp = e.getComponent<CMP_t>();
    if (eCmp) return *eCmp;

    // Create component if it doesn't exist
    auto& cmp = m_components.createComponent<CMP_t>( e.getID() );
    e.addComponent(cmp);
    return cmp;
}

const Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) const {
    auto found = std::find_if(begin(m_entities), end(m_entities), [&](const auto& e) {
        return e.getID() == eid;
    });

    if(found != end(m_entities))
        return found.base();
    return nullptr;
}

Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) {
    auto e = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);
    return const_cast<Entity_t*>(e);
}

template <typename CMP_t>
const CMP_t*
EntityManager_t::getRequiredComponent(const Component_t& cmp) const {
    if (auto* e = getEntityByID(cmp.getBelongingEntityID()))
        return e->template getComponent<CMP_t>();
    return nullptr;
}

template <typename CMP_t>
CMP_t*
EntityManager_t::getRequiredComponent(const Component_t& cmp) {
    auto reqCmp = const_cast<const EntityManager_t*>(this)->getRequiredComponent<CMP_t>(cmp);
    return const_cast<CMP_t*>(reqCmp);
}


} // namespace ECS

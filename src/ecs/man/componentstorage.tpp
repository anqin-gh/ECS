#pragma once
#include <algorithm>
#include "componentstorage.hpp"

namespace ECS {

inline ComponentStorage_t::ComponentStorage_t(std::size_t initial_size)
    : m_initial_size(initial_size)
{}

inline void
ComponentStorage_t::deleteComponentByTypeIDAndEntityID(ComponentTypeID_t cmpTypeID, EntityID_t eid) {
    auto found = m_components.find(cmpTypeID);
    if (found != end(m_components)) {
        found->second->deleteComponentByEntityID(eid);
    }
}

template<typename CMP_t>
CMP_t&
ComponentStorage_t::createComponent(EntityID_t eid) {
    auto& cmpVec = getComponents<CMP_t>();
    auto& cmp = cmpVec.emplace_back(eid);
    return cmp;
}

template<typename CMP_t>
const Vec_t<CMP_t>&
ComponentStorage_t::getComponents() const {
    if (auto found = getComponentsUtil<CMP_t>()) {
        return found->get();
    }
    throw std::runtime_error("WTFFFFF!!!!");
}

template<typename CMP_t>
Vec_t<CMP_t>&
ComponentStorage_t::getComponents() {
    if (auto found = const_cast<const ComponentStorage_t*>(this)->getComponentsUtil<CMP_t>())
        return const_cast<Vec_t<CMP_t>&>(found->get());
    return createComponentVector<CMP_t>();
}

template<typename CMP_t>
Opt_t<Ref_t<const Vec_t<CMP_t>>>
ComponentStorage_t::getComponentsUtil() const noexcept {
    auto found = m_components.find(CMP_t::getComponentTypeID());
    if (found != end(m_components)) {
        auto* cmpVec = dynamic_cast<ComponentVector_t<CMP_t>*>(found->second.get());
        return cmpVec->m_components;
    }
    return {};
}

template<typename CMP_t>
Vec_t<CMP_t>&
ComponentStorage_t::createComponentVector() {
    auto typeID{CMP_t::getComponentTypeID()};
    auto cmpVec = std::make_unique<ComponentVector_t<CMP_t>>();
    cmpVec->m_components.reserve(m_initial_size);
    auto* vecPtr = cmpVec.get();
    m_components[typeID] = std::move(cmpVec);
    return vecPtr->m_components;
}

template<typename CMP_t>
const CMP_t*
ComponentStorage_t::getComponentByEntityID(EntityID_t eid) const {
    auto& cmp_vect = getComponents<CMP_t>();
    auto found = std::find_if(begin(cmp_vect), end(cmp_vect), [eid](const auto& cmp) {
        return cmp.getBelongingEntityID() == eid;
    });
    if (found != std::end(cmp_vect)) return found.base();
    return nullptr;
}

template<typename CMP_t>
CMP_t*
ComponentStorage_t::getComponentByEntityID(EntityID_t eid) {
    // auto* cmp = const_cast<const ComponentStorage_t*>(this)->getComponentByEntityID<CMP_t>(eid);
    // return const_cast<CMP_t*>(cmp);
    // TODO: Repeated code!!!
    auto& cmp_vect = getComponents<CMP_t>();
    auto found = std::find_if(begin(cmp_vect), end(cmp_vect), [eid](const auto& cmp) {
        return cmp.getBelongingEntityID() == eid;
    });
    if (found != std::end(cmp_vect)) return found.base();
    return nullptr;
}

} // namespace ECS

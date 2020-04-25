#pragma once

#include <cmp/input.hpp>
#include <cmp/physics.hpp>
#include <cmp/render.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct ComponentVectorBase_t {
    virtual ~ComponentVectorBase_t() = default;
};

template<typename CMP_t>
struct ComponentVector_t : public ComponentVectorBase_t {
    Vec_t<CMP_t> m_components;
};

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size)
        : m_initial_size(initial_size)
    {}

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    template<typename CMP_t>
    CMP_t& createComponent(EntityID_t eid) {
        auto& cmpVec = getComponents<CMP_t>();
        auto& cmp = cmpVec.emplace_back(eid);
        return cmp;
    }

    template<typename CMP_t>
    Vec_t<CMP_t>& createComponentVector() {
        auto typeID{CMP_t::template getComponentTypeID<CMP_t>()};
        auto cmpVec = std::make_unique<ComponentVector_t<CMP_t>>();
        cmpVec->m_components.reserve(m_initial_size);
        auto* vecPtr = cmpVec.get();
        m_components[typeID] = std::move(cmpVec);
        return vecPtr->m_components;
    }

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const {
        if (auto found = getComponentsUtil<CMP_t>()) {
            return found->get();
        }
        throw "WTFFFFF!!!!";
    }

    template<typename CMP_t>
    Vec_t<CMP_t>& getComponents() {
        if (auto found = const_cast<const ComponentStorage_t*>(this)->getComponentsUtil<CMP_t>())
            return const_cast<Vec_t<CMP_t>&>(found->get());
        return createComponentVector<CMP_t>();
    }

private:
    template<typename CMP_t>
    Opt_t<Ref_t<const Vec_t<CMP_t>>> getComponentsUtil() const {
        auto found = m_components.find(CMP_t::template getComponentTypeID<CMP_t>());
        if (found != end(m_components)) {
            auto* cmpVec = dynamic_cast<ComponentVector_t<CMP_t>*>(found->second.get());
            return cmpVec->m_components;
        } 
        return {};
    }

private:
    std::size_t m_initial_size{100};
    UMap_t<ComponentTypeID_t, UPtr_t<ComponentVectorBase_t>> m_components;
};

} // namespace ECS

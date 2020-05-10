#pragma once
#include <ecs/util/typealiases.hpp>
#include "component.hpp"

namespace ECS {

struct Entity_t {
    explicit Entity_t() = default;

    constexpr EntityID_t getID() const noexcept { return ID; }
    
    template <typename CMP_t>
    void addComponent(CMP_t& cmp) {
        auto typeID = CMP_t::getComponentTypeID();
        m_components[typeID] = &cmp;
    }

    template <typename CMP_t>
    const CMP_t* getComponent() const noexcept {
        auto typeID = CMP_t::getComponentTypeID();
        auto found = m_components.find(typeID);
        if (found != std::end(m_components)) return dynamic_cast<const CMP_t*>(found->second);
        return nullptr;
    }

    template <typename CMP_t>
    CMP_t* getComponent() noexcept {
        auto cmp = const_cast<const Entity_t*>(this)->getComponent<CMP_t>();
        return const_cast<CMP_t*>(cmp);
    }

    auto begin() const noexcept { return std::begin(m_components); }
    auto begin()       noexcept { return std::begin(m_components); }
    auto end()   const noexcept { return std::end(m_components); }
    auto end()         noexcept { return std::end(m_components); }

private:
    inline static EntityID_t nextID{0};
    EntityID_t ID{++nextID};
    UMap_t<ComponentTypeID_t, Component_t*> m_components;
};

} // namespace ECS

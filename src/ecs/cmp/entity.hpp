#pragma once
#include <ecs/util/typealiases.hpp>
#include "component.hpp"

namespace ECS {

struct Entity_t {
    explicit Entity_t() = default;

    constexpr EntityID_t getID() const noexcept { return ID; }
    
    template <typename CMP_t>
    void addBelongingComponent(const CMP_t& cmp) {
        auto typeID = cmp.getComponentTypeID();
        m_components[typeID] = cmp.getID();
    }

    auto begin() const noexcept { return std::begin(m_components); }
    auto begin()       noexcept { return std::begin(m_components); }
    auto end()   const noexcept { return std::end(m_components); }
    auto end()         noexcept { return std::end(m_components); }

private:
    inline static EntityID_t nextID{0};
    EntityID_t ID{++nextID};
    UMap_t<ComponentTypeID_t, ComponentID_t> m_components;
};

} // namespace ECS

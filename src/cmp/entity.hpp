#pragma once
#include <cmp/input.hpp>
#include <cmp/physics.hpp>
#include <cmp/render.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct Entity_t {
    explicit Entity_t() = default;

    constexpr EntityID_t getID() const noexcept { return ID; }
    
    template <typename CMP_t>
    void addComponent(CMP_t& cmp) {
        auto typeID = CMP_t::template getComponentTypeID<CMP_t>();
        m_components[typeID] = &cmp;
    }

    template <typename CMP_t>
    const CMP_t* getComponent() const {
        auto typeID = CMP_t::template getComponentTypeID<CMP_t>();
        auto found = m_components.find(typeID);
        if (found != end(m_components)) return dynamic_cast<const CMP_t*>(found->second);
        return nullptr;
    }

    template <typename CMP_t>
    CMP_t* getComponent() {
        auto cmp = const_cast<const Entity_t*>(this)->getComponent<CMP_t>();
        return const_cast<CMP_t*>(cmp);
    }

private:
    inline static EntityID_t nextID{0};
    const EntityID_t ID{++nextID};
    UMap_t<ComponentTypeID_t, Component_t*> m_components;
};

} // namespace ECS

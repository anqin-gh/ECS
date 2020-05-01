#pragma once
#include <game/cmp/input.hpp>
#include <game/cmp/physics.hpp>
#include <game/cmp/render.hpp>
#include <ecs/util/typealiases.hpp>

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
    const CMP_t* getComponent() const {
        auto typeID = CMP_t::getComponentTypeID();
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
    UMap_t<ComponentTypeID_t, AbstractComponent_t*> m_components;
};

} // namespace ECS

#pragma once

#include <cmp/entity.hpp>
#include <cmp/physics.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size) {
        m_physics_components.reserve(initial_size);
    }

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    PhysicsComponent_t& createPhysicsComponent(EntityID_t eid);

    const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const { return m_physics_components; }
          Vec_t<PhysicsComponent_t>& getPhysicsComponents()       { return m_physics_components; }

private:
    Vec_t<PhysicsComponent_t> m_physics_components{};
};

} // namespace ECS

#pragma once

#include <cmp/input.hpp>
#include <cmp/physics.hpp>
#include <cmp/render.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size) {
        m_physics_components.reserve(initial_size);
        m_render_components.reserve(initial_size);
        m_input_components.reserve(initial_size);
    }

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    PhysicsComponent_t& createPhysicsComponent(EntityID_t eid);
    RenderComponent_t&  createRenderComponent(EntityID_t eid);
    InputComponent_t&   createInputComponent(EntityID_t eid);

    const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const { return m_physics_components; }
          Vec_t<PhysicsComponent_t>& getPhysicsComponents()       { return m_physics_components; }

    const Vec_t<RenderComponent_t>& getRenderComponents() const { return m_render_components; }
          Vec_t<RenderComponent_t>& getRenderComponents()       { return m_render_components; }

    const Vec_t<InputComponent_t>& getInputComponents() const { return m_input_components; }
          Vec_t<InputComponent_t>& getInputComponents()       { return m_input_components; }

private:
    Vec_t<PhysicsComponent_t> m_physics_components{};
    Vec_t<RenderComponent_t>  m_render_components{};
    Vec_t<InputComponent_t>   m_input_components{};
};

} // namespace ECS

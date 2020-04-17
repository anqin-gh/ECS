#include <man/componentstorage.hpp>

namespace ECS {

PhysicsComponent_t&
ComponentStorage_t::createPhysicsComponent(EntityID_t eid) {
    auto& cmp = m_physics_components.emplace_back(eid);
    return cmp;
}

RenderComponent_t&
ComponentStorage_t::createRenderComponent(EntityID_t eid) {
    auto& cmp = m_render_components.emplace_back(eid);
    return cmp;
}

InputComponent_t&
ComponentStorage_t::createInputComponent(EntityID_t eid) {
    auto& cmp = m_input_components.emplace_back(eid);
    return cmp;
}

} // namespace ECS

#include <man/componentstorage.hpp>

namespace ECS {

PhysicsComponent_t&
ComponentStorage_t::createPhysicsComponent(EntityID_t eid) {
    auto& cmp = m_physics_components.emplace_back(eid);
    return cmp;
}

} // namespace ECS

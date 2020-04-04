#include <man/componentstorage.hpp>

namespace ECS {

PhysicsComponent_t&
ComponentStorage_t::createPhysicsComponent() {
    auto& cmp = m_physics_components.emplace_back();
    return cmp;
}

} // namespace ECS

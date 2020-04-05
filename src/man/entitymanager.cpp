#include <cmp/physics.hpp>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

void EntityManager_t::createEntity(uint32_t x, uint32_t y, std::string filename) {
    auto& e  = m_entities.emplace_back(filename);
    auto& ph = m_components.createPhysicsComponent();
    e.phy = &ph;
    e.phy->x = x; e.phy->y = y;
}

} // namespace ECS

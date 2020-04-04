#include <algorithm>
#include <man/entitymanager.hpp>

namespace ECS {

EntityManager_t::EntityManager_t() {
    m_entities.reserve(kNUM_INITIAL_ENTITIES);
}

void EntityManager_t::createEntity(uint32_t x, uint32_t y, std::string filename) {
    auto& e  = m_entities.emplace_back(filename);
    e.x = x; e.y = y;
}

} // namespace ECS

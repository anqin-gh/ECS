#pragma once
#include <vector>
#include <cstdint>

#include <cmp/entity.hpp>
#include <man/componentstorage.hpp>
#include <util/gamecontext.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct EntityManager_t : public GameContext_t {
    
    explicit EntityManager_t();
    void createEntity(uint32_t x, uint32_t y, std::string filename);
    const Vec_t<Entity_t>& getEntities() const override { return m_entities; }
          Vec_t<Entity_t>& getEntities()       override { return m_entities; }

    const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const override { return m_components.getPhysicsComponents(); }
          Vec_t<PhysicsComponent_t>& getPhysicsComponents()       override { return m_components.getPhysicsComponents(); }

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

#pragma once
#include <string_view>
#include <cstdint>

#include <man/componentstorage.hpp>
#include <util/gamecontext.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct EntityManager_t : public GameContext_t {
    explicit EntityManager_t();

    Entity_t& createEntity(uint32_t x, uint32_t y, const std::string_view filename);

    void addInputComponent(Entity_t& e);

    const Vec_t<Entity_t>& getEntities() const override { return m_entities; }
          Vec_t<Entity_t>& getEntities()       override { return m_entities; }

    const Entity_t* getEntityByID(EntityID_t eid) const override;
          Entity_t* getEntityByID(EntityID_t eid)       override;

    const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const override { return m_components.getPhysicsComponents(); }
          Vec_t<PhysicsComponent_t>& getPhysicsComponents()       override { return m_components.getPhysicsComponents(); }

    const Vec_t<RenderComponent_t>& getRenderComponents() const override { return m_components.getRenderComponents(); }
          Vec_t<RenderComponent_t>& getRenderComponents()       override { return m_components.getRenderComponents(); }

    const Vec_t<InputComponent_t>& getInputComponents() const override { return m_components.getInputComponents(); }
          Vec_t<InputComponent_t>& getInputComponents()       override { return m_components.getInputComponents(); }

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

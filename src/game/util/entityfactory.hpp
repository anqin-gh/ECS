#pragma once
#include <string_view>
#include <cstdint>
#include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/collider.hpp>
#include <game/cmp/physics.hpp>
#include <game/cmp/spawner.hpp>

struct EnitityFactory_t {
    explicit EnitityFactory_t(ECS::EntityManager_t& man);

    EnitityFactory_t(const EnitityFactory_t&) = delete;
    EnitityFactory_t(EnitityFactory_t&&) = delete;
    EnitityFactory_t& operator=(const EnitityFactory_t&) = delete;
    EnitityFactory_t& operator=(EnitityFactory_t&&) = delete;

    ECS::Entity_t& createEntity(uint32_t x, uint32_t y, const std::string_view filename);
    ECS::Entity_t& createPlayer(uint32_t x, uint32_t y);
    ECS::Entity_t& createBlade(uint32_t x, uint32_t y);

    template <typename Action_t>
    ECS::Entity_t& createSpawner(uint32_t x, uint32_t y, Action_t&& action) {
        auto& e   = m_ent_man.createEntity();

        auto& spw = m_ent_man.addComponent<SpawnerComponent_t>(e);
        spw.spawningAction = action;

        auto& ph  = m_ent_man.addComponent<PhysicsComponent_t>(e);
        ph.x = x; ph.y = y;
        ph.vx = 0; ph.vy = 1;

        auto& cl  = m_ent_man.addComponent<ColliderComponent_t>(e);
        cl.box.x_left  = 0;
        cl.box.x_right = 20;
        cl.box.y_up    = 0;
        cl.box.y_down  = 20;

        return e;
    }

private:
    ECS::EntityManager_t& m_ent_man;
};

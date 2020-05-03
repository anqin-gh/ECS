#include <ecs/cmp/entity.hpp>
#include <ecs/man/entitymanager.hpp>
#include <game/cmp/collider.hpp>
#include <game/cmp/input.hpp>
#include <game/cmp/physics.hpp>
#include <game/cmp/render.hpp>
#include <game/cmp/spawner.hpp>
#include "entityfactory.hpp"

EnitityFactory_t::EnitityFactory_t(ECS::EntityManager_t& man)
    : m_ent_man{man}
{}

ECS::Entity_t&
EnitityFactory_t::createEntity(uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = m_ent_man.createEntity();

    auto& ph  = m_ent_man.addComponent<PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;

    auto& rn = m_ent_man.addComponent<RenderComponent_t>(e);
    rn.loadFromFile(filename);

    auto& cl = m_ent_man.addComponent<ColliderComponent_t>(e);
    cl.box.x_left  = 10;
    cl.box.x_right = rn.w - 10;
    cl.box.y_up    = 10;
    cl.box.y_down  = rn.h - 10;

    return e;
}

ECS::Entity_t&
EnitityFactory_t::createPlayer(uint32_t x, uint32_t y) {
    auto& e = createEntity(x, y, "assets/jerry.png");
    m_ent_man.addComponent<InputComponent_t>(e);
    return e;
}

ECS::Entity_t&
EnitityFactory_t::createBlade(uint32_t x, uint32_t y) {
    auto& e = createEntity(x, y, "assets/blade.png");
    auto* phy = e.getComponent<PhysicsComponent_t>();
    phy->vx = 1;
    phy->vy = 1;
    return e;
}

ECS::Entity_t&
EnitityFactory_t::createSpawner(uint32_t x, uint32_t y) {
    auto& e   = m_ent_man.createEntity();

    auto& spw = m_ent_man.addComponent<SpawnerComponent_t>(e);
    spw.spawningAction = [&](uint32_t x, uint32_t y) {
        createBlade(x, y);
    };

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

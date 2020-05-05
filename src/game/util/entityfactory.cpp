#include <game/cmp/debug.hpp>
#include <game/cmp/input.hpp>
#include <game/cmp/render.hpp>
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

    m_ent_man.addComponent<DebugComponent_t>(e);

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

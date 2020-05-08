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
    cl.box.box_root = { 10, rn.w - 10, 10, rn.h - 10 };

    m_ent_man.addComponent<DebugComponent_t>(e);

    return e;
}

ECS::Entity_t&
EnitityFactory_t::createPlayer(uint32_t x, uint32_t y) {
    auto& e = createEntity(x, y, "assets/characters/Yellow_Front1.png");
    m_ent_man.addComponent<InputComponent_t>(e);

    auto* ren = e.getComponent<RenderComponent_t>();
    auto* col = e.getComponent<ColliderComponent_t>();
    if (col && ren) {
        col->box.box_root = { 0, ren->w, 21, ren->h };  // outside box
        auto& children_level1 = col->box.children;
        children_level1.reserve(3); // reserve for head, body & legs boxes

        auto& head = children_level1.emplace_back(16, ren->w - 16,  25,  48);
        head.children.emplace_back(37, ren->w - 37,  25,  48);
        
        auto& body_box = children_level1.emplace_back(13, ren->w - 13,  48, 131);
        auto& body_children = body_box.children;
        body_children.reserve(3); // reserve for middle box & 2 arms
        body_children.emplace_back(16, ren->w - 16, 51, 116);
        body_children.emplace_back(ren->w - 16, ren->w - 5, 68, 123);
        body_children.emplace_back(5, 16, 68, 123);

        auto& legs_box = children_level1.emplace_back(17, ren->w - 17, 131, 147);
        legs_box.children.reserve(2);
        legs_box.children.emplace_back(20, 46, 131, 158);
        legs_box.children.emplace_back(ren->w - 46, ren->w - 20, 131, 158);
    }

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

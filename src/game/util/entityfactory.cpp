#include <game/cmp/debug.hpp>
#include <game/cmp/health.hpp>
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

    auto* ren = m_ent_man.getComponentByEntityID<RenderComponent_t>(e.getID());
    auto* col = m_ent_man.getComponentByEntityID<ColliderComponent_t>(e.getID());
    if (col && ren) {
        col->box.box_root = { 0, ren->w, 21, ren->h };  // outside box
        auto& children_level1 = col->box.children;
        children_level1.reserve(7); // reserve for head, body & legs boxes

        children_level1.emplace_back(37, ren->w - 37,  21,  30);    // top head box
        children_level1.emplace_back(25, ren->w - 25,  30,  50);    // bottom head box
        
        children_level1.emplace_back(16, ren->w - 16, 50, 147);     // central square
        children_level1.emplace_back(ren->w - 16, ren->w, 68, 123); // right arm
        children_level1.emplace_back(0, 16, 68, 123);               // left arm

        children_level1.emplace_back(20, 46, 147, 158);
        children_level1.emplace_back(ren->w - 46, ren->w - 20, 147, 158);
    }
    
    auto& h_cmp = m_ent_man.addComponent<HealthComponent_t>(e);
    h_cmp.health = 5;

    std::cout << "Player created with EID: " << e.getID() << std::endl;

    return e;
}

ECS::Entity_t&
EnitityFactory_t::createBlade(uint32_t x, uint32_t y) {
    auto& e = createEntity(x, y, "assets/blade.png");
    auto* phy = m_ent_man.getComponentByEntityID<PhysicsComponent_t>(e.getID());
    phy->vx = 1;
    m_ent_man.addComponent<HealthComponent_t>(e);

    std::cout << "Blade created with EID: " << e.getID() << std::endl;

    return e;
}

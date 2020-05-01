#include <chrono>
#include <thread>

#include <cstdint>
#include <cstdio>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <man/entitymanager.hpp>
#include <sys/collision.hpp>
#include <sys/input.hpp>
#include <sys/physics.hpp>
#include <sys/render.hpp>
#include <sys/spawn.hpp>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

using namespace std::chrono_literals;
constexpr auto kSPF { 1ms };

ECS::Entity_t& createEntity(ECS::EntityManager_t& man, uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = man.createEntity();

    auto& ph  = man.addComponent<ECS::PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;

    auto& rn = man.addComponent<ECS::RenderComponent_t>(e);
    rn.loadFromFile(filename);

    auto& cl = man.addComponent<ECS::ColliderComponent_t>(e);
    cl.box.x_left  = 0;
    cl.box.x_right = rn.w;
    cl.box.y_up    = 0;
    cl.box.y_down  = rn.h;

    return e;
}

ECS::Entity_t& createPlayer(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/jerry.png");
    man.addComponent<ECS::InputComponent_t>(e);
    return e;
}

ECS::Entity_t& createBlade(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/blade.png");
    auto* phy = e.getComponent<ECS::PhysicsComponent_t>();
    phy->vx = 1;
    phy->vy = 1;
    return e;
}

ECS::Entity_t& createSpawner(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e   = man.createEntity();

    [[maybe_unused]]auto& sp = man.addComponent<ECS::SpawnerComponent_t>(e);

    auto& ph  = man.addComponent<ECS::PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;
    ph.vx = 0; ph.vy = 1;

    auto& cl  = man.addComponent<ECS::ColliderComponent_t>(e);
    cl.box.x_left  = 0;
    cl.box.x_right = 20;
    cl.box.y_up    = 0;
    cl.box.y_down  = 20;

    return e;
}


int main() {
    try {
        // Entities
        ECS::EntityManager_t entityMan;
        createBlade(entityMan, 290, 160);
        createBlade(entityMan, 100,  10);
        createPlayer(entityMan, 10,  10);
        createSpawner(entityMan, 200, 150);

        // Systems
        const ECS::RenderSystem_t<ECS::EntityManager_t> render{kSCRWIDTH, kSCRHEIGHT};
        ECS::PhysicsSystem_t<ECS::EntityManager_t> physics;
        ECS::CollisionSystem_t<ECS::EntityManager_t> collision{kSCRWIDTH, kSCRHEIGHT};
        ECS::InputSystem_t<ECS::EntityManager_t> input;
        ECS::SpawnSystem_t<ECS::EntityManager_t> spawn;

        using clk = std::chrono::steady_clock;
        // main loop
        while(render.update(entityMan)) {
            auto lastTime = clk::now();
            input.update(entityMan);
            physics.update(entityMan);
            collision.update(entityMan);
            spawn.update(entityMan);
            auto elapsed = clk::now() - lastTime;
            if(elapsed < kSPF)
                std::this_thread::sleep_for( kSPF - elapsed );
        }
    } catch(...) {
        std::puts("Capturada");
    }

    return 0;
}
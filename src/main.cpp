#include <chrono>
#include <thread>

#include <cstdint>
#include <cstdio>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <ecs/man/entitymanager.tpp>
#include <game/sys/collision.tpp>
#include <game/sys/input.tpp>
#include <game/sys/physics.tpp>
#include <game/sys/render.tpp>
#include <game/sys/spawn.tpp>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

using namespace std::chrono_literals;
constexpr auto kSPF { 1ms };

ECS::Entity_t& createEntity(ECS::EntityManager_t& man, uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = man.createEntity();

    auto& ph  = man.addComponent<PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;

    auto& rn = man.addComponent<RenderComponent_t>(e);
    rn.loadFromFile(filename);

    auto& cl = man.addComponent<ColliderComponent_t>(e);
    cl.box.x_left  = 10;
    cl.box.x_right = rn.w - 10;
    cl.box.y_up    = 10;
    cl.box.y_down  = rn.h - 10;

    return e;
}

ECS::Entity_t& createPlayer(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/jerry.png");
    man.addComponent<InputComponent_t>(e);
    return e;
}

ECS::Entity_t& createBlade(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/blade.png");
    auto* phy = e.getComponent<PhysicsComponent_t>();
    phy->vx = 1;
    phy->vy = 1;
    return e;
}

ECS::Entity_t& createSpawner(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e   = man.createEntity();

    [[maybe_unused]]auto& sp = man.addComponent<SpawnerComponent_t>(e);

    auto& ph  = man.addComponent<PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;
    ph.vx = 0; ph.vy = 1;

    auto& cl  = man.addComponent<ColliderComponent_t>(e);
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
        const RenderSystem_t<ECS::EntityManager_t> render{kSCRWIDTH, kSCRHEIGHT};
        PhysicsSystem_t<ECS::EntityManager_t> physics;
        CollisionSystem_t<ECS::EntityManager_t> collision{kSCRWIDTH, kSCRHEIGHT};
        InputSystem_t<ECS::EntityManager_t> input;
        SpawnSystem_t<ECS::EntityManager_t> spawn;

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
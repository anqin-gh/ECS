#include <chrono>
#include <thread>

#include <cstdint>
#include <cstdio>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <ecs/man/entitymanager.hpp>
#include <game/sys/collision.tpp>
#include <game/sys/input.tpp>
#include <game/sys/physics.tpp>
#include <game/sys/render.tpp>
#include <game/sys/spawn.tpp>
#include <game/util/entityfactory.hpp>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

using namespace std::chrono_literals;
constexpr auto kSPF { 1ms };

int main() {
    try {
        // Entities
        ECS::EntityManager_t entityMan;
        EnitityFactory_t entityFactory{entityMan};
        entityFactory.createBlade(290, 160);
        entityFactory.createBlade(100,  10);
        entityFactory.createPlayer(10,  10);
        entityFactory.createSpawner(200, 150);

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
#include <chrono>
#include <iostream>
#include <exception>
#include <thread>

#include <cstdint>
#include <cstdio>

#include <ecs/man/entitymanager.tpp>
#include <game/sys/collision.tpp>
#include <game/sys/garbagecolection.tpp>
#include <game/sys/health.tpp>
#include <game/sys/input.tpp>
#include <game/sys/physics.tpp>
#include <game/sys/render.tpp>
#include <game/sys/spawn.tpp>
#include <game/util/entityfactory.hpp>

constexpr uint32_t kSCRWIDTH  { 850 };
constexpr uint32_t kSCRHEIGHT { 480 };

using namespace std::chrono_literals;
constexpr auto kSPF { 1ms };

int main() {
    try {
        // Entities
        ECS::EntityManager_t entityMan;
        EnitityFactory_t entityFactory{entityMan};
        // entityFactory.createBlade(150, 50);
        // entityFactory.createBlade(190, 10);
        // entityFactory.createBlade(150, 130);
        // entityFactory.createBlade(190, 90);
        // entityFactory.createPlayer(10,  10);

        entityFactory.createBlade(320, 160);
        entityFactory.createBlade(100,  10);
        entityFactory.createPlayer(10,  10);
        entityFactory.createSpawner(200, 150, 
            [&](const auto& spw) {
                if (auto* phy = entityMan.getRequiredComponent<PhysicsComponent_t>(spw)) {
                    entityFactory.createBlade(phy->x, phy->y);
                }
            });

        // Systems
        const RenderSystem_t<ECS::EntityManager_t> render{kSCRWIDTH, kSCRHEIGHT};
        render.setDebug(true);

        const PhysicsSystem_t<ECS::EntityManager_t> physics;
        const CollisionSystem_t<ECS::EntityManager_t> collision{kSCRWIDTH, kSCRHEIGHT};
        const HealthSystem_t<ECS::EntityManager_t> health;
        const InputSystem_t<ECS::EntityManager_t> input;
        const SpawnSystem_t<ECS::EntityManager_t> spawn;
        const GarbageCollectionSystem_t<ECS::EntityManager_t> garbageCollection;

        using clk = std::chrono::steady_clock;
        // main loop
        while( !input.isKeyPressed(XK_Escape) ) {
            auto lastTime = clk::now();
            spawn.update(entityMan);
            input.update(entityMan);
            physics.update(entityMan);
            collision.update(entityMan);
            render.update(entityMan);
            health.update(entityMan);
            garbageCollection.update(entityMan);

            auto elapsed = clk::now() - lastTime;
            if(elapsed < kSPF)
                std::this_thread::sleep_for( kSPF - elapsed );
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch(...) {
        std::puts("Capturada");
    }

    return 0;
}
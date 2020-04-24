#include <chrono>
#include <thread>

#include <cstdint>
#include <cstdio>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <sys/collision.hpp>
#include <sys/input.hpp>
#include <sys/physics.hpp>
#include <sys/render.hpp>
#include <man/entitymanager.hpp>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

using namespace std::chrono_literals;
constexpr auto kSPF { 1ms };

int main() {
    try {
        // Entities
        ECS::EntityManager_t entityMan;
        entityMan.createEntity( 20, 40, "assets/jerry.png");
        entityMan.createEntity( 80, 10, "assets/jerry.png");
        auto& e = entityMan.createEntity(200, 170, "assets/jerry.png");
        entityMan.addInputComponent(e);

        // Systems
        const ECS::RenderSystem_t<ECS::EntityManager_t> render{kSCRWIDTH, kSCRHEIGHT};
        ECS::PhysicsSystem_t<ECS::EntityManager_t> physics;
        ECS::CollisionSystem_t<ECS::EntityManager_t> collision;
        ECS::InputSystem_t<ECS::EntityManager_t> input;

        using clk = std::chrono::steady_clock;
        // main loop
        while(render.update(entityMan)) {
            auto lastTime = clk::now();
            input.update(entityMan);
            physics.update(entityMan);
            collision.update(entityMan);
            auto elapsed = clk::now() - lastTime;
            if(elapsed < kSPF)
                std::this_thread::sleep_for( kSPF - elapsed );
        }
    } catch(...) {
        std::puts("Capturada");
    }

    return 0;
}
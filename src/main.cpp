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

int main() {
    try {
        ECS::EntityManager_t entityMan;
        entityMan.createEntity( 20, 40, "assets/jerry.png");
        entityMan.createEntity( 80, 10, "assets/jerry.png");
        auto& e = entityMan.createEntity(200, 170, "assets/jerry.png");
        entityMan.addInputComponent(e);
        const ECS::RenderSystem_t render{kSCRWIDTH, kSCRHEIGHT};
        ECS::PhysicsSystem_t physics;
        ECS::CollisionSystem_t collision;
        ECS::InputSystem_t input;
        while(render.update(entityMan)) {
            input.update(entityMan);
            physics.update(entityMan);
            collision.update(entityMan);
        }
    } catch(...) {
        std::puts("Capturada");
    }

    return 0;
}
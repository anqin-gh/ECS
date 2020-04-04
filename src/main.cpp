#include <exception>
#include <iostream>
#include <string>

#include <cstdint>
#include <cstdio>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <sys/collision.hpp>
#include <sys/physics.hpp>
#include <sys/render.hpp>
#include <man/entitymanager.hpp>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

int main() {
    int i = 1;
    if(*(char *)&i == 1) std::cout << "Little-endian\n";
    else std::cout << "Big-endian\n";

    try {
        ECS::EntityManager_t entityMan;
        entityMan.createEntity(70, 150, "assets/jerry.png");
        const ECS::RenderSystem_t render{kSCRWIDTH, kSCRHEIGHT};
        ECS::PhysicsSystem_t physics;
        ECS::CollisionSystem_t collision;
        while(render.update(entityMan)) {
            physics.update(entityMan);
            collision.update(entityMan);
        }
    } catch(...) {
        std::puts("Capturada4");
    }

    return 0;
}
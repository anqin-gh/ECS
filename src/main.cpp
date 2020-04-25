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

ECS::Entity_t& createEntity(ECS::EntityManager_t& man, uint32_t x, uint32_t y, const std::string_view filename) {
    auto& e   = man.createEntity();

    auto& ph  = man.addComponent<ECS::PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;
    e.addComponent(ph);

    auto& rn = man.addComponent<ECS::RenderComponent_t>(e);
    rn.loadFromFile(filename);
    e.addComponent(rn);

    return e;
}

ECS::Entity_t& createPlayer(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/jerry.png");
    
    man.addComponent<ECS::InputComponent_t>(e);
    
    auto* phy = e.getComponent<ECS::PhysicsComponent_t>();
    phy->vx = 0;
    phy->vy = 0;

    return e;
}

ECS::Entity_t& createBlade(ECS::EntityManager_t& man, uint32_t x, uint32_t y) {
    auto& e = createEntity(man, x, y, "assets/blade.png");
    return e;
}


int main() {
    try {
        // Entities
        ECS::EntityManager_t entityMan;
        createBlade(entityMan, 90, 160);
        createBlade(entityMan, 80, 100);
        createPlayer(entityMan, 200, 170);

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
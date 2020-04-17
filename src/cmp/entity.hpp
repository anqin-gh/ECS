#pragma once
#include <util/typealiases.hpp>

struct InputComponent_t;
struct PhysicsComponent_t;
struct RenderComponent_t;

namespace ECS {

struct Entity_t {
    explicit Entity_t() = default;

    constexpr EntityID_t getID() const noexcept { return ID; }

    PhysicsComponent_t* phy{nullptr};
    RenderComponent_t*  ren{nullptr};
    InputComponent_t*   inp{nullptr};

private:
    inline static EntityID_t nextID{0};
    const EntityID_t ID{++nextID};
};

} // namespace ECS

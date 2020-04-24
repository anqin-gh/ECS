#pragma once
#include <cmp/input.hpp>
#include <cmp/physics.hpp>
#include <cmp/render.hpp>
#include <util/typealiases.hpp>

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

#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct BoundingBox_t {
    uint32_t x_left{0}, x_right{0};
    uint32_t y_up{0}, y_down{0};
};


struct ColliderComponent_t : public ECS::ComponentBase_t<ColliderComponent_t> {
    explicit ColliderComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t{eid}
    {}

    BoundingBox_t box;
};

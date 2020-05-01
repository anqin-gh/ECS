#pragma once
#include <string_view>
#include <cstdint>

#include <cmp/component.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct BoundingBox_t {
    uint32_t x_left{0}, x_right{0};
    uint32_t y_up{0}, y_down{0};
};


struct ColliderComponent_t : public Component_t {
    explicit ColliderComponent_t(EntityID_t eid)
        : Component_t{eid}
    {}

    BoundingBox_t box;
};

} // namespace ECS

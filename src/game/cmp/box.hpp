#pragma once
#include <cstdint>
#include <ecs/util/typealiases.hpp>

struct BoundingBox_t {
    uint32_t x_left{0}, x_right{0};
    uint32_t y_up{0}, y_down{0};
};

struct BoundingBoxNode_t {
    explicit BoundingBoxNode_t() = default;
    explicit BoundingBoxNode_t(uint32_t xl, uint32_t xr, uint32_t yu, uint32_t yd)
        : box_root{xl, xr, yu, yd}
    {}

    BoundingBox_t box_root;
    bool collided{false};
    ECS::Vec_t<BoundingBoxNode_t> children;
};

#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>
#include "box.hpp"

struct ColliderComponent_t : public ECS::ComponentBase_t<ColliderComponent_t> {
    explicit ColliderComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t{eid}
    {}

    uint8_t mask { 0xFF };
    BoundingBoxNode_t box;
};

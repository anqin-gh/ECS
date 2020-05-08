#pragma once
#include <ecs/cmp/component.hpp>
#include "box.hpp"

struct ColliderComponent_t : public ECS::ComponentBase_t<ColliderComponent_t> {
    explicit ColliderComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t{eid}
    {}

    BoundingBoxNode_t box;
};

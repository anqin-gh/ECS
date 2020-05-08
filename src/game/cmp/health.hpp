#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct HealthComponent_t : public ECS::ComponentBase_t<HealthComponent_t> {
    explicit HealthComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t{eid}
    {}

    uint64_t health { 1 };
};

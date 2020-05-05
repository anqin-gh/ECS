#pragma once
#include <ecs/cmp/component.hpp>
#include <game/util/colors.hpp>

struct DebugComponent_t : public ECS::ComponentBase_t<DebugComponent_t> {
    explicit DebugComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {}

    uint32_t color_lines{colors::kRed};
    uint32_t color_filling{colors::kOrange};
};

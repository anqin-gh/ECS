#pragma once
#include <ecs/cmp/component.hpp>
#include <X11/keysym.h>
#include <X11/X.h>

struct InputComponent_t : public ECS::ComponentBase_t<InputComponent_t> {
    explicit InputComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {}

    static constexpr KeySym key_left     { XK_o };
    static constexpr KeySym key_right    { XK_p };
    static constexpr KeySym key_up       { XK_q };
    static constexpr KeySym key_down     { XK_a };
};

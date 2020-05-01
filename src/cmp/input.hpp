#pragma once
#include <cmp/component.hpp>
#include <X11/keysym.h>
#include <X11/X.h>

namespace ECS {

struct InputComponent_t : public Component_t {
    explicit InputComponent_t(EntityID_t eid)
        : Component_t(eid)
    {}

    static constexpr KeySym key_left     { XK_o };
    static constexpr KeySym key_right    { XK_p };
    static constexpr KeySym key_up       { XK_q };
    static constexpr KeySym key_down     { XK_a };
};

} // namespace ECS

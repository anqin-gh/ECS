#pragma once

#include <util/keyboard.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t;

struct InputSystem_t {
    explicit InputSystem_t();

    bool update(GameContext_t& context) const;

private:
    static void onKeyPress(KeySym k);
    static void onKeyRelease(KeySym k);

    inline static Keyboard_t ms_keyboard{};
};

} // namespace ECS

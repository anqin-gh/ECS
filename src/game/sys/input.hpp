#pragma once
#include <game/cmp/input.hpp>
#include <ecs/util/keyboard.hpp>
#include <ecs/util/typealiases.hpp>

template<typename GameCTX_t>
struct InputSystem_t {
    explicit InputSystem_t();

    bool update(GameCTX_t& ctx) const;

private:
    static void onKeyPress(KeySym k)   { ms_keyboard.keyPressed(k); }
    static void onKeyRelease(KeySym k) { ms_keyboard.keyReleased(k); }

    inline static ECS::Keyboard_t ms_keyboard{};
};

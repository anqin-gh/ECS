#pragma once
#include <ecs/util/keyboard.hpp>

template<typename GameCTX_t>
struct InputSystem_t {
    explicit InputSystem_t();

    void update(GameCTX_t& ctx) const noexcept;
    bool isKeyPressed(KeySym k) const noexcept;

private:
    static void onKeyPress(KeySym k)   noexcept { ms_keyboard.keyPressed(k); }
    static void onKeyRelease(KeySym k) noexcept { ms_keyboard.keyReleased(k); }

    inline static ECS::Keyboard_t ms_keyboard{};
};

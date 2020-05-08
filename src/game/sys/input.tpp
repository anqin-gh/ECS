#pragma once
#include <game/cmp/input.hpp>
#include <game/cmp/physics.hpp>
#include "input.hpp"

extern "C" {
    #ifdef CROSSWIN
        #include <tinyPTC/src/windows/tinyptc.h>
    #else
        #include <tinyPTC/src/linux/tinyptc.h>
    #endif
}

template<typename GameCTX_t>
InputSystem_t<GameCTX_t>::InputSystem_t() {
    ptc_set_on_keypress( onKeyPress );
    ptc_set_on_keyrelease( onKeyRelease );
}

template<typename GameCTX_t>
void InputSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    ptc_process_events();

    for( auto& inp : ctx.template getComponents<InputComponent_t>() ) {
        if (auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(inp)) {
            phy->vx = phy->vy = 0;
            if (ms_keyboard.isKeyPressed( inp.key_left   )) phy->vx = -1;
            if (ms_keyboard.isKeyPressed( inp.key_right  )) phy->vx =  1;
            if (ms_keyboard.isKeyPressed( inp.key_up     )) phy->vy = -1;
            if (ms_keyboard.isKeyPressed( inp.key_down   )) phy->vy =  1;
        }
    }
}

template<typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::isKeyPressed(KeySym k) const noexcept {
    return ms_keyboard.isKeyPressed(k);
}
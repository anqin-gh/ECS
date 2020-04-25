#pragma once
#include <cmp/physics.hpp>
#include <cmp/input.hpp>
#include <util/keyboard.hpp>
#include <util/typealiases.hpp>

namespace ECS {

template<typename GameCTX_t>
struct InputSystem_t {
    explicit InputSystem_t() {
        ptc_set_on_keypress( onKeyPress );
        ptc_set_on_keyrelease( onKeyRelease );
    }

    bool update(GameCTX_t& ctx) const {
        ptc_process_events();

        for( auto& inp : ctx.template getComponents<InputComponent_t>() ) {
            if (auto* e = ctx.template getEntityByID( inp.getBelongingEntityID() )) {
                if (auto* phy = e->template getComponent<PhysicsComponent_t>()) {
                    phy->vx = phy->vy = 0;
                    if(ms_keyboard.isKeyPressed( inp.key_left   )) phy->vx = -1;
                    if(ms_keyboard.isKeyPressed( inp.key_right  )) phy->vx =  1;
                    if(ms_keyboard.isKeyPressed( inp.key_up     )) phy->vy = -1;
                    if(ms_keyboard.isKeyPressed( inp.key_down   )) phy->vy =  1;
                }
            }
        }
        return true;
    }

private:
    static void onKeyPress(KeySym k)   { ms_keyboard.keyPressed(k); }
    static void onKeyRelease(KeySym k) { ms_keyboard.keyReleased(k); }

    inline static Keyboard_t ms_keyboard{};
};

} // namespace ECS

#include <game/cmp/physics.hpp>
#include "input.hpp"

template<typename GameCTX_t>
InputSystem_t<GameCTX_t>::InputSystem_t() {
    ptc_set_on_keypress( onKeyPress );
    ptc_set_on_keyrelease( onKeyRelease );
}

template<typename GameCTX_t>
bool InputSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    ptc_process_events();

    for( auto& inp : ctx.template getComponents<InputComponent_t>() ) {
        if (auto* e = ctx.getEntityByID( inp.getBelongingEntityID() )) {
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

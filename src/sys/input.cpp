extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}

#include <cmp/physics.hpp>
#include <sys/input.hpp>
#include <util/gamecontext.hpp>
#include <util/keyboard.hpp>
#include <util/typealiases.hpp>

namespace ECS {

InputSystem_t::InputSystem_t() {
    ptc_set_on_keypress( onKeyPress );
    ptc_set_on_keyrelease( onKeyRelease );
}

void InputSystem_t::onKeyPress(KeySym k) {
    ms_keyboard.keyPressed(k);
}

void InputSystem_t::onKeyRelease(KeySym k) {
    ms_keyboard.keyReleased(k);
}

bool InputSystem_t::update(GameContext_t& context) const {
    ptc_process_events();

    for( auto& inp : context.getInputComponents() ) {
        auto* e = context.getEntityByID( inp.getBelongingEntityID() );
        if(e && e->phy) {
            auto& phy = *(e->phy);
            if(ms_keyboard.isKeyPressed( inp.key_left   )) phy.vx = -1;
            if(ms_keyboard.isKeyPressed( inp.key_right  )) phy.vx =  1;
            if(ms_keyboard.isKeyPressed( inp.key_up     )) phy.vy = -1;
            if(ms_keyboard.isKeyPressed( inp.key_down   )) phy.vy =  1;
        }
    }

    return true;
}

} // namespace ECS

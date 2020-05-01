#include <ecs/util/keyboard.hpp>
#include <ecs/util/utils.hpp>

namespace ECS {

bool Keyboard_t::isKeyPressed(KeySym k) const noexcept {
    if( auto found = getIterator(k) )
        return (*found)->second;
    return false;
}

void Keyboard_t::keyPressed(KeySym k) noexcept {
    if( auto found = getIterator(k) )
        (*found)->second = true;
}

void Keyboard_t::keyReleased(KeySym k) noexcept {
    if( auto found = getIterator(k) )
        (*found)->second = false;
}

Keyboard_t::KeyboardItr
Keyboard_t::getIterator(KeySym k) noexcept {
    auto it = const_cast<const Keyboard_t*>(this)->getIterator(k);
    return remove_constness(m_pressed_keys, *it);
}

Keyboard_t::KeyboardConstItr
Keyboard_t::getIterator(KeySym k) const noexcept {
    auto found = m_pressed_keys.find(k);
    if(found != end(m_pressed_keys))
        return found;
    return {};
}

} // namespace ECS

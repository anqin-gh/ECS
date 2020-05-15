#pragma once
#include "garbagecolection.hpp"

template<typename GameCTX_t>
constexpr void GarbageCollectionSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    ctx.destroyEntities();
}

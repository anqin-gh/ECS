#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/health.hpp>
#include <game/sys/health.hpp>

template<typename GameCTX_t>
constexpr void
HealthSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    for (auto& h : ctx.template getComponents<HealthComponent_t>()) {
        if (const auto* col = ctx.template getRequiredComponent<ColliderComponent_t>(hlth)) {

        }
    }
}

#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/physics.hpp>
#include <game/cmp/render.hpp>
#include <game/cmp/spawner.hpp>
#include "spawn.hpp"

template <typename GameCTX_t>
constexpr void
SpawnSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    using clk = std::chrono::steady_clock;
    for (auto& spw : ctx.template getComponents<SpawnerComponent_t>()) {
        auto elapsed{clk::now() - spw.last_spawn_time};
        if (spw.to_be_spawned > 0 && elapsed > spw.spawn_interval) {
            spw.spawningAction(spw);
            --spw.to_be_spawned;
            spw.last_spawn_time = clk::now();
        }
    }
}

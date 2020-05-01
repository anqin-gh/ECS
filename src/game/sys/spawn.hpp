#pragma once
#include <string_view>
#include <cstdint>

struct SpawnerComponent_t;
struct PhysicsComponent_t;

template<typename GameCTX_t>
struct SpawnSystem_t {
    explicit SpawnSystem_t() = default;

    void update(GameCTX_t& ctx) const;
    PhysicsComponent_t* getRequiredComponent(GameCTX_t& ctx, const SpawnerComponent_t& spw) const;
    void spawnDeVerdad(GameCTX_t& ctx, uint32_t x, uint32_t y, const std::string_view filename) const;
};

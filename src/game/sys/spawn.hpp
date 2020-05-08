#pragma once
#include <string_view>
#include <cstdint>

template<typename GameCTX_t>
struct SpawnSystem_t {
    explicit SpawnSystem_t() = default;
    constexpr void update(GameCTX_t& ctx) const noexcept;
};

#pragma once

template<typename GameCTX_t>
struct HealthSystem_t {
    explicit HealthSystem_t() = default;

    constexpr void update(GameCTX_t& ctx) const noexcept;
};

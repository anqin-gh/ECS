#pragma once

template<typename GameCTX_t>
struct PhysicsSystem_t {
    explicit PhysicsSystem_t() = default;

    void update(GameCTX_t& ctx) const noexcept;
};

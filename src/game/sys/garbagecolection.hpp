#pragma once

template<typename GameCTX_t>
struct GarbageCollectionSystem_t {
    explicit GarbageCollectionSystem_t() = default;

    constexpr void update(GameCTX_t& ctx) const noexcept;
};

#pragma once

struct BoundingBoxNode_t;

template<typename GameCTX_t>
struct HealthSystem_t {
    explicit HealthSystem_t() = default;

    constexpr void update(GameCTX_t& ctx) const noexcept;

private:
    constexpr bool hasLeafNodeColided(const BoundingBoxNode_t& box_node) const noexcept;
};

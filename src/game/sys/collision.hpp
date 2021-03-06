#pragma once
#include <cstdint>

template<typename GameCTX_t>
struct CollisionSystem_t {
    explicit CollisionSystem_t(uint32_t w, uint32_t h);
    constexpr void update(GameCTX_t& ctx) const noexcept;

private:
    constexpr void setUncollided(BoundingBoxNode_t& ctx) const noexcept;
    constexpr void checkBoundaryCollisions(const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept;
    constexpr BoundingBox_t convert2ScreenCoordinates(const BoundingBox_t& box, uint32_t x, uint32_t y) const noexcept;
    constexpr void checkEntityCollision(uint32_t x1, uint32_t y1, BoundingBoxNode_t& col1, uint32_t x2, uint32_t y2, BoundingBoxNode_t& col2) const noexcept;

    const uint32_t m_w{0}, m_h{0};
};

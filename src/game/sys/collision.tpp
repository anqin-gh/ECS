#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/physics.hpp>
#include "collision.hpp"

template<typename GameCTX_t>
CollisionSystem_t<GameCTX_t>::CollisionSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
{}

template<typename GameCTX_t>
bool CollisionSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    auto& col_cmp_vec = ctx.template getComponents<ColliderComponent_t>();

    for (auto& col : col_cmp_vec) col.box.collided = false;

    for (std::size_t i = 0; i < col_cmp_vec.size(); ++i) {
        auto& col1 = col_cmp_vec[i];
        if (auto* phy1 = ctx.template getRequiredComponent<PhysicsComponent_t>(col1)) {
            checkBoundaryCollisions(col1, *phy1);

            for (std::size_t j = i+1; j < col_cmp_vec.size(); ++j) {
                auto& col2 = col_cmp_vec[j];
                if (auto* phy2 = ctx.template getRequiredComponent<PhysicsComponent_t>(col2)) {
                    checkEntityCollision(phy1->x, phy1->y, col1, phy2->x, phy2->y, col2);
                }
            }
        }
    }
    return true;
}

using namespace std;
template<typename GameCTX_t>
constexpr void
CollisionSystem_t<GameCTX_t>::checkBoundaryCollisions(const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept {
    auto [ xl, xr, yu, yd ] = convert2ScreenCoordinates(col.box.box_root, phy.x, phy.y);

    // Detect collisions
    if (xl >= m_w || xr >= m_w) { phy.x -= phy.vx; phy.vx = -phy.vx; }
    if (yu >= m_h || yd >= m_h) { phy.y -= phy.vy; phy.vy = -phy.vy; }
}

template<typename GameCTX_t>
constexpr void
CollisionSystem_t<GameCTX_t>::checkEntityCollision(uint32_t x1, uint32_t y1, ColliderComponent_t& col1, uint32_t x2, uint32_t y2, ColliderComponent_t& col2) const noexcept {
    auto [ xl1, xr1, yu1, yd1 ] = convert2ScreenCoordinates(col1.box.box_root, x1, y1);
    auto [ xl2, xr2, yu2, yd2 ] = convert2ScreenCoordinates(col2.box.box_root, x2, y2);

    auto isIntervalIntersecting = [](uint32_t l1, uint32_t r1, uint32_t l2, uint32_t r2) {
        if (l2 > r1 || l1 > r2) return false;
        return true;
    };

    if (    isIntervalIntersecting(xl1, xr1, xl2, xr2)
        &&  isIntervalIntersecting(yu1, yd1, yu2, yd2))
    {
        col1.box.collided = true;
        col2.box.collided = true;
    }
}

template<typename GameCTX_t>
constexpr BoundingBox_t
CollisionSystem_t<GameCTX_t>::convert2ScreenCoordinates(const BoundingBox_t& box, uint32_t x, uint32_t y) const noexcept {
    auto xl{ x + box.x_left  };
    auto xr{ x + box.x_right };
    auto yu{ y + box.y_up    };
    auto yd{ y + box.y_down  };

    return { xl, xr, yu, yd };
}

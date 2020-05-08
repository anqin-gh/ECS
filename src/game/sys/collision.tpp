#pragma once
#include <game/cmp/collider.hpp>
#include <game/cmp/physics.hpp>
#include "collision.hpp"

template<typename GameCTX_t>
CollisionSystem_t<GameCTX_t>::CollisionSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
{}

template<typename GameCTX_t>
constexpr void
CollisionSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    auto& col_cmp_vec = ctx.template getComponents<ColliderComponent_t>();

    for (auto& col : col_cmp_vec) setUncollided(col.box);

    for (std::size_t i = 0; i < col_cmp_vec.size(); ++i) {
        auto& col1 = col_cmp_vec[i];
        if (auto* phy1 = ctx.template getRequiredComponent<PhysicsComponent_t>(col1)) {
            checkBoundaryCollisions(col1, *phy1);

            for (std::size_t j = i+1; j < col_cmp_vec.size(); ++j) {
                auto& col2 = col_cmp_vec[j];

                if ( !(col1.mask & col2.mask) ) continue;

                if (auto* phy2 = ctx.template getRequiredComponent<PhysicsComponent_t>(col2)) {
                    checkEntityCollision(phy1->x, phy1->y, col1.box, phy2->x, phy2->y, col2.box);
                }
            }
        }
    }
}

template<typename GameCTX_t>
constexpr void
CollisionSystem_t<GameCTX_t>::setUncollided(BoundingBoxNode_t& box_node) const noexcept {
    box_node.collided = false;
    for (auto& child : box_node.children) setUncollided(child);
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
CollisionSystem_t<GameCTX_t>::checkEntityCollision(uint32_t x1, uint32_t y1, BoundingBoxNode_t& box1, uint32_t x2, uint32_t y2, BoundingBoxNode_t& box2) const noexcept {
    auto [ xl1, xr1, yu1, yd1 ] = convert2ScreenCoordinates(box1.box_root, x1, y1);
    auto [ xl2, xr2, yu2, yd2 ] = convert2ScreenCoordinates(box2.box_root, x2, y2);

    // Check interval intersection in a generic axis
    auto isIntervalIntersecting = [](uint32_t l1, uint32_t r1, uint32_t l2, uint32_t r2) {
        if (l2 > r1 || l1 > r2) return false;
        return true;
    };

    // Check interval intersection in both axes
    if (isIntervalIntersecting(xl1, xr1, xl2, xr2) && isIntervalIntersecting(yu1, yd1, yu2, yd2)) {

        box1.collided = true;
        box2.collided = true;
        
        if ( !box1.children.empty() ) {
            for (auto& child : box1.children) checkEntityCollision(x1, y1, child, x2, y2, box2);
        } else if ( !box2.children.empty() ) {
            for (auto& child : box2.children) checkEntityCollision(x1, y1, box1, x2, y2, child);
        }
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

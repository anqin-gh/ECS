#pragma once
#include <cstdint>

struct ColliderComponent_t;
struct PhysicsComponent_t;

template<typename GameCTX_t>
struct CollisionSystem_t {
    explicit CollisionSystem_t(uint32_t w, uint32_t h);

    bool update(GameCTX_t& ctx) const;
    PhysicsComponent_t* getRequiredComponent(GameCTX_t& ctx, const ColliderComponent_t& col) const;

    uint32_t m_w{0}, m_h{0};
};

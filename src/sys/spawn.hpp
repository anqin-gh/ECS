#pragma once
#include <cmp/spawner.hpp>

namespace ECS {

template<typename GameCTX_t>
struct SpawnSystem_t {
    explicit SpawnSystem_t() = default;

    void update(GameCTX_t& ctx) const {
        using clk = std::chrono::steady_clock;
        for (auto& spw : ctx.template getComponents<SpawnerComponent_t>()) {
            auto elapsed{clk::now() - spw.last_spawn_time};
            if (spw.to_be_spawned > 0 && elapsed > spw.spawn_interval) {
                if (auto* phy = getRequiredComponent(ctx, spw)) {
                    spawnDeVerdad(ctx, phy->x, phy->y, "assets/blade.png");
                    --spw.to_be_spawned;
                    spw.last_spawn_time = clk::now();
                }
            }
        }
    }

    PhysicsComponent_t*
    getRequiredComponent(GameCTX_t& ctx, const SpawnerComponent_t& spw) const {
        if (auto* e = ctx.getEntityByID(spw.getBelongingEntityID()))
            return e->template getComponent<PhysicsComponent_t>();
        return nullptr;
    }

    void spawnDeVerdad(GameCTX_t& ctx, uint32_t x, uint32_t y, const std::string_view filename) const {
        auto& e   = ctx.createEntity();

        auto& ph  = ctx.template addComponent<ECS::PhysicsComponent_t>(e);
        ph.x = x; ph.y = y;
        ph.vx = ph.vy = 1;
        e.addComponent(ph);

        auto& rn = ctx.template addComponent<ECS::RenderComponent_t>(e);
        rn.loadFromFile(filename);
        e.addComponent(rn);

        auto& cl = ctx.template addComponent<ECS::ColliderComponent_t>(e);
        cl.box.x_left  = 0;
        cl.box.x_right = rn.w;
        cl.box.y_up    = 0;
        cl.box.y_down  = rn.h;
    }
};

} // namespace ECS

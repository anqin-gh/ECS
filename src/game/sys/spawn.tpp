#include <game/cmp/spawner.hpp>
#include "spawn.hpp"

template <typename GameCTX_t>
void SpawnSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
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

template <typename GameCTX_t>
PhysicsComponent_t*
SpawnSystem_t<GameCTX_t>::getRequiredComponent(GameCTX_t& ctx, const SpawnerComponent_t& spw) const {
    if (auto* e = ctx.getEntityByID(spw.getBelongingEntityID()))
        return e->template getComponent<PhysicsComponent_t>();
    return nullptr;
}

template <typename GameCTX_t>
void SpawnSystem_t<GameCTX_t>::spawnDeVerdad(GameCTX_t& ctx, uint32_t x, uint32_t y, const std::string_view filename) const {
    auto& e   = ctx.createEntity();

    auto& ph  = ctx.template addComponent<PhysicsComponent_t>(e);
    ph.x = x; ph.y = y;
    ph.vx = ph.vy = 1;
    e.addComponent(ph);

    auto& rn = ctx.template addComponent<RenderComponent_t>(e);
    rn.loadFromFile(filename);
    e.addComponent(rn);

    auto& cl = ctx.template addComponent<ColliderComponent_t>(e);
    cl.box.x_left  = 0;
    cl.box.x_right = rn.w;
    cl.box.y_up    = 0;
    cl.box.y_down  = rn.h;
}

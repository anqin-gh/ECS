#pragma once
#include <chrono>
#include <functional>
#include <ecs/cmp/component.hpp>

using namespace std::chrono_literals;

struct SpawnerComponent_t : public ECS::ComponentBase_t<SpawnerComponent_t> {
    explicit SpawnerComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {}

    std::function<void(const SpawnerComponent_t&)> spawningAction{};
    
    using clk = std::chrono::steady_clock;
    clk::time_point last_spawn_time{clk::now()};
    clk::duration spawn_interval{2s};
    std::size_t to_be_spawned{2};
};

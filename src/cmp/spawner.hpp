#pragma once
#include <chrono>
#include <cmp/component.hpp>

namespace ECS {

using namespace std::chrono_literals;

struct SpawnerComponent_t : public ComponentBase_t<SpawnerComponent_t> {
    explicit SpawnerComponent_t(EntityID_t eid)
        : ComponentBase_t(eid)
    {}

    using clk = std::chrono::steady_clock;
    clk::time_point last_spawn_time{clk::now()};
    clk::duration spawn_interval{2s};
    std::size_t to_be_spawned{2};
};

} // namespace ECS

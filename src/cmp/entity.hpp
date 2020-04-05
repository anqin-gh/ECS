#pragma once

#include <string>
#include <cstdint>

#include <picoPNG/src/picopng.hpp>
#include <util/typealiases.hpp>

struct PhysicsComponent_t;

namespace ECS {

struct Entity_t {
    explicit Entity_t(uint32_t w_, uint32_t h_);
    explicit Entity_t(std::string filename);

    PhysicsComponent_t* phy{nullptr};
    uint32_t  w{0},  h{0};
    Vec_t<uint32_t> sprite{};
};

} // namespace ECS

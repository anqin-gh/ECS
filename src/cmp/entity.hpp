#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

#include <cmp/physics.hpp>
#include <picoPNG/src/picopng.hpp>

namespace ECS {

struct Entity_t {
    explicit Entity_t(uint32_t w_, uint32_t h_);
    explicit Entity_t(std::string filename);

    PhysicsComponent_t* phy{nullptr};
    uint32_t  w{0},  h{0};
    std::vector<uint32_t> sprite{};
};

} // namespace ECS

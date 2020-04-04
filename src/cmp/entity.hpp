#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

#include <picoPNG/src/picopng.hpp>

namespace ECS {

struct Entity_t {
    explicit Entity_t(uint32_t w_, uint32_t h_);
    explicit Entity_t(std::string filename);

    uint32_t  w{0},  h{0};
    uint32_t  x{0},  y{0};
    uint32_t vx{1}, vy{1};
    std::vector<uint32_t> sprite{};
};

} // namespace ECS

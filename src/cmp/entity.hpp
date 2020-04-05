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

    EntityID_t getID() const { return ID; }

    PhysicsComponent_t* phy{nullptr};
    uint32_t  w{0},  h{0};
    Vec_t<uint32_t> sprite{};

private:
    inline static EntityID_t nextID{0};
    const EntityID_t ID{++nextID};
};

} // namespace ECS

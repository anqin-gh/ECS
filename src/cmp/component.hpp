#pragma once
#include <iostream>
#include <cstdint>

#include <util/typealiases.hpp>

namespace ECS {

struct Component_t {
    explicit Component_t(EntityID_t eid)
        : entityID{eid}
    {}

    ComponentID_t getID() const { return ID; }
    ComponentID_t getBelongingEntityID() const { return entityID; }

private:
    inline static ComponentID_t nextID{0};
    const ComponentID_t ID{++nextID};
    const EntityID_t entityID{0};
};

} // namespace ECS

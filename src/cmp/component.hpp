#pragma once
#include <iostream>
#include <cstdint>

#include <util/typealiases.hpp>

namespace ECS {

struct Component_t {
    explicit Component_t(EntityID_t eid)
        : entityID{eid}
    {}

    virtual ~Component_t() = default;

    template<typename CMP_t>
    static ComponentTypeID_t getComponentTypeID() {
        static ComponentTypeID_t typeID{++nextTypeID};
        return typeID;
    }

    constexpr ComponentID_t getID() const noexcept { return ID; }
    constexpr ComponentID_t getBelongingEntityID() const noexcept { return entityID; }

private:
    inline static ComponentTypeID_t nextTypeID{0};

    inline static ComponentID_t nextID{0};
    const ComponentID_t ID{++nextID};
    const EntityID_t entityID{0};
};

} // namespace ECS

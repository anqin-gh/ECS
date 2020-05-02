#pragma once
#include <cstdint>

#include <ecs/util/typealiases.hpp>

namespace ECS {

struct Component_t {
    virtual ~Component_t() = default;

    virtual ComponentID_t getID() const noexcept = 0;
    virtual ComponentID_t getBelongingEntityID() const noexcept = 0;

protected:
    template <typename CMP_t>
    static ComponentTypeID_t getComponentTypeID() noexcept {
        static ComponentTypeID_t typeID{++nextTypeID};
        return typeID;
    }

private:
    inline static ComponentTypeID_t nextTypeID{0};
};

template <typename CMP_t>
struct ComponentBase_t : public Component_t {
protected:
    explicit ComponentBase_t(EntityID_t eid)
        : entityID{eid}
    {}

public:
    constexpr static ComponentTypeID_t getComponentTypeID() noexcept { return Component_t::getComponentTypeID<CMP_t>(); }

    ComponentID_t getID() const noexcept override { return ID; }
    ComponentID_t getBelongingEntityID() const noexcept override { return entityID; }

private:
    inline static ComponentID_t nextID{0};
    const ComponentID_t ID{++nextID};
    const EntityID_t entityID{0};
};

} // namespace ECS

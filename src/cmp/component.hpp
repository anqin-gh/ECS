#pragma once
#include <cstdint>

#include <util/typealiases.hpp>

namespace ECS {

struct AbstractComponent_t {
    virtual ~AbstractComponent_t() = default;

    template <typename CMP_t>
    static ComponentTypeID_t getComponentTypeID() noexcept {
        static ComponentTypeID_t typeID{++nextTypeID};
        return typeID;
    }

private:
    inline static ComponentTypeID_t nextTypeID{0};
};

template <typename CMP_t>
struct ComponentBase_t : public AbstractComponent_t {
protected:
    explicit ComponentBase_t(EntityID_t eid)
        : entityID{eid}
    {}

public:
    static ComponentTypeID_t getComponentTypeID() noexcept {
        return AbstractComponent_t::getComponentTypeID<CMP_t>();
    }

    constexpr ComponentID_t getID() const noexcept { return ID; }
    constexpr ComponentID_t getBelongingEntityID() const noexcept { return entityID; }

private:
    inline static ComponentID_t nextID{0};
    const ComponentID_t ID{++nextID};
    const EntityID_t entityID{0};
};

} // namespace ECS

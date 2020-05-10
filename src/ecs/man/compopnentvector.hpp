#pragma once
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct ComponentVectorBase_t {
    ComponentVectorBase_t(const ComponentVectorBase_t&) = delete;
    ComponentVectorBase_t& operator=(const ComponentVectorBase_t&) = delete;
    ComponentVectorBase_t(ComponentVectorBase_t&&) = delete;
    ComponentVectorBase_t& operator=(ComponentVectorBase_t&&) = delete;

    virtual ~ComponentVectorBase_t() = default;

    virtual void deleteComponentByEntityID(EntityID_t eid) = 0;

protected:
    ComponentVectorBase_t() = default;
};

template<typename CMP_t>
struct ComponentVector_t : public ComponentVectorBase_t {
    explicit ComponentVector_t() = default;

    void deleteComponentByEntityID(EntityID_t eid) override final;

    Vec_t<CMP_t> m_components;
};

} // namespace ECS

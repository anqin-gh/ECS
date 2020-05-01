#pragma once
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct ComponentVectorBase_t {
    virtual ~ComponentVectorBase_t() = default;
};

template<typename CMP_t>
struct ComponentVector_t : public ComponentVectorBase_t {
    Vec_t<CMP_t> m_components;
};

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size);

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    template<typename CMP_t>
    CMP_t& createComponent(EntityID_t eid);

    template<typename CMP_t>
    Vec_t<CMP_t>& createComponentVector();

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const;

    template<typename CMP_t>
    Vec_t<CMP_t>& getComponents();

private:
    template<typename CMP_t>
    Opt_t<Ref_t<const Vec_t<CMP_t>>> getComponentsUtil() const;

private:
    std::size_t m_initial_size{100};
    UMap_t<ComponentTypeID_t, UPtr_t<ComponentVectorBase_t>> m_components;
};

} // namespace ECS

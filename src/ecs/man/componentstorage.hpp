#pragma once
#include <ecs/man/compopnentvector.tpp>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size);

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    void deleteComponentByTypeIDAndEntityID(ComponentTypeID_t cmpTypeID, EntityID_t eid);

    template<typename CMP_t> CMP_t& createComponent(EntityID_t eid);

    template<typename CMP_t> const Vec_t<CMP_t>& getComponents() const;
    template<typename CMP_t>       Vec_t<CMP_t>& getComponents();

    template<typename CMP_t> const CMP_t* getComponentByEntityID(EntityID_t eid) const;
    template<typename CMP_t>       CMP_t* getComponentByEntityID(EntityID_t eid);

private:
    template<typename CMP_t> Opt_t<Ref_t<const Vec_t<CMP_t>>> getComponentsUtil() const noexcept;

    template<typename CMP_t> const CMP_t* getComponentMatchingEntityIDInContainer(EntityID_t eid, const Vec_t<CMP_t>& cmps) const noexcept;

    template<typename CMP_t> Vec_t<CMP_t>& createComponentVector();

private:
    std::size_t m_initial_size{100};
    UMap_t<ComponentTypeID_t, UPtr_t<ComponentVectorBase_t>> m_components;
};

} // namespace ECS

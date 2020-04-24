#pragma once
#include <string_view>
#include <cstdint>

#include <cmp/entity.hpp>
#include <man/componentstorage.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct EntityManager_t {
    explicit EntityManager_t();

    Entity_t& createEntity(uint32_t x, uint32_t y, const std::string_view filename);

    void addInputComponent(Entity_t& e);
   
    const Vec_t<Entity_t>& getEntities() const { return m_entities; }
          Vec_t<Entity_t>& getEntities()       { return m_entities; }

    const Entity_t* getEntityByID(EntityID_t eid) const;
          Entity_t* getEntityByID(EntityID_t eid)      ;

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const { return m_components.getComponents<CMP_t>(); }

    template<typename CMP_t>
          Vec_t<CMP_t>& getComponents()       { return m_components.getComponents<CMP_t>(); }

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

#pragma once
#include <ecs/man/componentstorage.tpp>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct Entity_t;
struct Component_t;

struct EntityManager_t {
    explicit EntityManager_t();

    Entity_t& createEntity();

    template<typename CMP_t>
    CMP_t& addComponent(Entity_t& e);
   
    const Vec_t<Entity_t>& getEntities() const noexcept;
          Vec_t<Entity_t>& getEntities()       noexcept;

    const Entity_t* getEntityByID(EntityID_t eid) const;
          Entity_t* getEntityByID(EntityID_t eid)      ;

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const;

    template<typename CMP_t>
          Vec_t<CMP_t>& getComponents()      ;

	template <typename CMP_t>
	const CMP_t* getRequiredComponent(const Component_t& cmp) const;

	template <typename CMP_t>
	CMP_t* getRequiredComponent(const Component_t& cmp);

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

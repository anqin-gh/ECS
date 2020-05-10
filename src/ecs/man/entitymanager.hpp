#pragma once
#include <ecs/man/componentstorage.tpp>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct EntityManager_t {
    explicit EntityManager_t();

    Entity_t& createEntity();

	void destroyEntityByID(EntityID_t eid);
   
    const Vec_t<Entity_t>& getEntities() const noexcept;
          Vec_t<Entity_t>& getEntities()       noexcept;

	const Entity_t* getEntityByID(EntityID_t eid) const noexcept;
		  Entity_t* getEntityByID(EntityID_t eid) 		noexcept;

    template<typename CMP_t> CMP_t& addComponent(Entity_t& e);

    template<typename CMP_t> const Vec_t<CMP_t>& getComponents() const noexcept;
    template<typename CMP_t> 	   Vec_t<CMP_t>& getComponents()       noexcept;

	template <typename ReqCMP_t, typename CMP_t> const ReqCMP_t* getRequiredComponent(const CMP_t& cmp) const noexcept;
	template <typename ReqCMP_t, typename CMP_t> 	   ReqCMP_t* getRequiredComponent(const CMP_t& cmp)       noexcept;

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

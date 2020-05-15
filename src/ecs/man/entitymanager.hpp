#pragma once
#include <ecs/man/componentstorage.tpp>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct EntityManager_t {
    explicit EntityManager_t();

    Entity_t& createEntity();

	const Entity_t* getEntityByID(EntityID_t eid) const noexcept;
		  Entity_t* getEntityByID(EntityID_t eid) 		noexcept;

    template<typename CMP_t> CMP_t& addComponent(Entity_t& e);

    template<typename CMP_t> const Vec_t<CMP_t>& getComponents() const noexcept;
    template<typename CMP_t> 	   Vec_t<CMP_t>& getComponents()       noexcept;
    
    template<typename CMP_t> const CMP_t* getComponentByEntityID(EntityID_t eid) const noexcept;
    template<typename CMP_t> 	   CMP_t* getComponentByEntityID(EntityID_t eid)       noexcept;

	template <typename ReqCMP_t, typename CMP_t> const ReqCMP_t* getRequiredComponent(const CMP_t& cmp) const noexcept;
	template <typename ReqCMP_t, typename CMP_t> 	   ReqCMP_t* getRequiredComponent(const CMP_t& cmp)       noexcept;

	void markEntityIDToBeDestroyed(EntityID_t eid);
	void destroyEntities();

private:
    void destroyEntityByID(EntityID_t eid);

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    Vec_t<EntityID_t> m_to_be_destroyed{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

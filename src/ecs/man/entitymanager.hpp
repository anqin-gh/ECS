#pragma once
#include <algorithm>
#include <iostream>
#include <ecs/cmp/entity.hpp>
#include <ecs/man/componentstorage.hpp>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct EntityManager_t {
    explicit EntityManager_t() {
		m_entities.reserve(kNUM_INITIAL_ENTITIES);
	}

    Entity_t& createEntity() { return m_entities.emplace_back(); }

	template<typename CMP_t>
	CMP_t& addComponent(Entity_t& e) {
		auto* eCmp = e.getComponent<CMP_t>();
		if (eCmp) return *eCmp;

		// Create component if it doesn't exist
		auto& cmp = m_components.createComponent<CMP_t>( e.getID() );
		e.addComponent(cmp);
		return cmp;
	}
   
    const Vec_t<Entity_t>& getEntities() const noexcept { return m_entities; }
          Vec_t<Entity_t>& getEntities()       noexcept { return m_entities; }

	const Entity_t* getEntityByID(EntityID_t eid) const noexcept {
		auto found = std::find_if(begin(m_entities), end(m_entities), [&](const auto& e) {
			return e.getID() == eid;
		});

		if(found != end(m_entities))
			return found.base();
		return nullptr;
	}

	Entity_t* getEntityByID(EntityID_t eid) noexcept {
		auto e = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);
		return const_cast<Entity_t*>(e);
	}

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const noexcept { return m_components.getComponents<CMP_t>(); }

    template<typename CMP_t>
          Vec_t<CMP_t>& getComponents()       noexcept { return m_components.getComponents<CMP_t>(); }

	template <typename ReqCMP_t, typename CMP_t>
	const ReqCMP_t* getRequiredComponent(const CMP_t& cmp) const noexcept {
		if (auto* e = getEntityByID(cmp.getBelongingEntityID()))
			return e->template getComponent<ReqCMP_t>();
		return nullptr;
	}

	template <typename ReqCMP_t, typename CMP_t>
	ReqCMP_t* getRequiredComponent(const CMP_t& cmp) noexcept {
		auto reqCmp = const_cast<const EntityManager_t*>(this)->getRequiredComponent<ReqCMP_t>(cmp);
		return const_cast<ReqCMP_t*>(reqCmp);
	}

	void destroyEntityByID(EntityID_t eid) {
		std::cout << "Entity[" << eid << "] is dead!\n";
		if (auto* entity = getEntityByID(eid)) {
			for (auto& [ typeID, cmp ] : *entity) {
				m_components.deleteComponentByTypeIDAndEntityID(typeID, eid);
			}
			auto found = find_if(begin(m_entities), end(m_entities), [eid](const Entity_t& e) {
				return e.getID() == eid;
			});

			// auto& last_entity = *(end(m_entities)-1);
			// for (auto& [ typeID, cmp ] : last_entity) {

			// }

			// std::iter_swap(found, end(m_entities)-1);
			// m_entities.pop_back();
		}
	}

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    Vec_t<Entity_t> m_entities{};
    ComponentStorage_t m_components{kNUM_INITIAL_ENTITIES};
};

} // namespace ECS

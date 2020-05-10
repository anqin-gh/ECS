#pragma once
#include <algorithm>
#include <ecs/util/typealiases.hpp>

namespace ECS {

struct ComponentVectorBase_t {
    virtual ~ComponentVectorBase_t() = default;
    virtual void deleteComponentByEntityID(EntityID_t eid) = 0;
};

template<typename CMP_t>
struct ComponentVector_t : public ComponentVectorBase_t {
    Vec_t<CMP_t> m_components;
    void deleteComponentByEntityID(EntityID_t eid) override final {
        // TODO: Linear search!!!
        auto found = std::find_if(begin(m_components), end(m_components), [eid](const CMP_t& cmp) {
                return cmp.getBelongingEntityID() == eid;
            });

        if (found != end(m_components)) {   // TODO: Error management!!!
            std::cout << "Deleting Component[EID: " << eid << ", CTID: " << CMP_t::getComponentTypeID() << ", CID: " << found->getID() << ']' << std::endl;
            auto& swapped = *(end(m_components)-1);
            std::cout << "Swapped  Component[EID: " << swapped.getBelongingEntityID() << ", CTID: " << swapped.getComponentTypeID() << ", CID: " << swapped.getID() << ']'  << std::endl;
            // std::iter_swap(found, end(m_components)-1);
            // m_components.pop_back();
        }
    }
};

struct ComponentStorage_t {
    explicit ComponentStorage_t(std::size_t initial_size)
        : m_initial_size(initial_size)
    {}

    ComponentStorage_t() = delete;
    ComponentStorage_t(ComponentStorage_t const&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t const&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    template<typename CMP_t>
    CMP_t& createComponent(EntityID_t eid) {
        auto& cmpVec = getComponents<CMP_t>();
        auto& cmp = cmpVec.emplace_back(eid);
        return cmp;
    }

    template<typename CMP_t>
    Vec_t<CMP_t>& createComponentVector() {
        auto typeID{CMP_t::getComponentTypeID()};
        auto cmpVec = std::make_unique<ComponentVector_t<CMP_t>>();
        cmpVec->m_components.reserve(m_initial_size);
        auto* vecPtr = cmpVec.get();
        m_components[typeID] = std::move(cmpVec);
        return vecPtr->m_components;
    }

    template<typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const {
        if (auto found = getComponentsUtil<CMP_t>()) {
            return found->get();
        }
        throw "WTFFFFF!!!!";
    }

    template<typename CMP_t>
    Vec_t<CMP_t>& getComponents() {
        if (auto found = const_cast<const ComponentStorage_t*>(this)->getComponentsUtil<CMP_t>())
            return const_cast<Vec_t<CMP_t>&>(found->get());
        return createComponentVector<CMP_t>();
    }

    void deleteComponentByTypeIDAndEntityID(ComponentTypeID_t cmpTypeID, EntityID_t eid) {
        auto found = m_components.find(cmpTypeID);
        if (found != end(m_components)) {
            found->second->deleteComponentByEntityID(eid);
        }
    }

private:
    template<typename CMP_t>
    Opt_t<Ref_t<const Vec_t<CMP_t>>> getComponentsUtil() const noexcept {
        auto found = m_components.find(CMP_t::getComponentTypeID());
        if (found != end(m_components)) {
            auto* cmpVec = dynamic_cast<ComponentVector_t<CMP_t>*>(found->second.get());
            return cmpVec->m_components;
        }
        return {};
    }

private:
    std::size_t m_initial_size{100};
    UMap_t<ComponentTypeID_t, UPtr_t<ComponentVectorBase_t>> m_components;
};

} // namespace ECS

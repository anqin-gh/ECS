#include "compopnentvector.hpp"

namespace ECS {

template<typename CMP_t>
void
ComponentVector_t<CMP_t>::deleteComponentByEntityID(EntityID_t eid) {
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

} // namespace ECS

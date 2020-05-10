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
        *found = m_components.back();
        m_components.pop_back();
    }
}

} // namespace ECS

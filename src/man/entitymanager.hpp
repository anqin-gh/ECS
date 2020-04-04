#pragma once
#include <vector>
#include <cstdint>

#include <cmp/entity.hpp>
#include <util/gamecontext.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct EntityManager_t : public GameContext_t {
    
    explicit EntityManager_t();
    void createEntity(uint32_t x, uint32_t y, std::string filename);
    const VecEntities_t& getEntities() const override { return m_entities; }
          VecEntities_t& getEntities()       override { return m_entities; }

private:
    static constexpr std::size_t kNUM_INITIAL_ENTITIES{1000};
    VecEntities_t m_entities{};
};

} // namespace ECS

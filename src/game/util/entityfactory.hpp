#pragma once
#include <string_view>
#include <cstdint>

namespace ECS {

struct Entity_t;
struct EntityManager_t;

}

struct EnitityFactory_t {
    explicit EnitityFactory_t(ECS::EntityManager_t& man);

    EnitityFactory_t(const EnitityFactory_t&) = delete;
    EnitityFactory_t(EnitityFactory_t&&) = delete;
    EnitityFactory_t& operator=(const EnitityFactory_t&) = delete;
    EnitityFactory_t& operator=(EnitityFactory_t&&) = delete;

    ECS::Entity_t& createEntity(uint32_t x, uint32_t y, const std::string_view filename);
    ECS::Entity_t& createPlayer(uint32_t x, uint32_t y);
    ECS::Entity_t& createBlade(uint32_t x, uint32_t y);
    ECS::Entity_t& createSpawner(uint32_t x, uint32_t y);

private:
    ECS::EntityManager_t& m_ent_man;
};

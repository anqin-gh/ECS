#pragma once
#include <string_view>
#include <cstdint>

#include <ecs/cmp/component.hpp>
#include <ecs/util/typealiases.hpp>

struct RenderComponent_t : public ECS::ComponentBase_t<RenderComponent_t> {
    explicit RenderComponent_t(ECS::EntityID_t eid);

    void loadFromFile(const std::string_view filename);

    uint32_t  w{0},  h{0};
    ECS::Vec_t<uint32_t> sprite{};

private:
    auto loadPNGFileIntoVector(const std::string_view filename);
    void initSpriteFromABGRData(const ECS::Vec_t<unsigned char>& pixels);

};

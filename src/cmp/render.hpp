#pragma once
#include <string_view>
#include <cstdint>

#include <cmp/component.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct RenderComponent_t : public ComponentBase_t<RenderComponent_t> {
    explicit RenderComponent_t(EntityID_t eid);

    void loadFromFile(const std::string_view filename);

    uint32_t  w{0},  h{0};
    Vec_t<uint32_t> sprite{};

private:
    auto loadPNGFileIntoVector(const std::string_view filename);
    void initSpriteFromABGRData(const Vec_t<unsigned char>& pixels);

};

} // namespace ECS

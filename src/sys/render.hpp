#pragma once
#include <memory>
#include <cstdint>

#include <cmp/entity.hpp>
#include <util/typealiases.hpp>

namespace ECS {

struct GameContext_t;

struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t w, uint32_t h);
    ~RenderSystem_t();
    void drawAllEntities(const Vec_t<Entity_t>& entities) const;
    bool update(const GameContext_t& context) const;

private:
    static constexpr uint32_t kR = 0x00FF0000;
    const uint32_t m_w { 0 }, m_h { 0 };
    std::unique_ptr<uint32_t[]> m_framebuffer { nullptr };
};

} // namespace ECS

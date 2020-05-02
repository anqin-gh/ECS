#pragma once
#include <cstdint>
#include <memory>

template<typename GameCTX_t>
struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t w, uint32_t h);
    ~RenderSystem_t();

    bool update(GameCTX_t& ctx) const;
    void drawAllEntities(GameCTX_t& ctx) const;
    void renderSpriteWithClipping(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const;

private:
    static constexpr uint32_t kR = 0x00FF0000;
    const uint32_t m_w { 0 }, m_h { 0 };
    ECS::UPtr_t<uint32_t[]> m_framebuffer { nullptr };
};

#pragma once
#include <cstdint>
#include <memory>

struct RenderComponent_t;
struct PhysicsComponent_t;

template<typename GameCTX_t>
struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t w, uint32_t h);
    ~RenderSystem_t();

    bool update(GameCTX_t& ctx) const;
    constexpr void setDebug(bool v) const noexcept { m_debug = v; }

private:
    void drawAllEntities(GameCTX_t& ctx) const;
    constexpr void renderSpriteWithClipping(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const noexcept;
    constexpr uint32_t* getScreenPos(uint32_t x, uint32_t y) const noexcept { return m_framebuffer.get() + m_w * y + x; };
    constexpr auto calculateClipping(uint32_t spritePos, uint32_t size, uint32_t lim) const noexcept;
    void drawDebugLines(const GameCTX_t& ctx) const noexcept;
    constexpr void drawBoxLines(const BoundingBoxNode_t& box, uint32_t x, uint32_t y, uint32_t color) const noexcept;
    constexpr void drawClippedHorizontalLine(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color) const noexcept;
    constexpr void drawClippedVerticalLine(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color) const noexcept;
    constexpr void drawLine(uint32_t* screen, uint32_t size, uint32_t stride, uint32_t color) const noexcept;
    constexpr void drawFullBox(const BoundingBoxNode_t& box, uint32_t x, uint32_t y, uint32_t color) const noexcept;
    constexpr void drawSquare(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) const noexcept;

private:
    mutable bool m_debug{false};

    const uint32_t m_w { 0 }, m_h { 0 };
    ECS::UPtr_t<uint32_t[]> m_framebuffer { nullptr };
};

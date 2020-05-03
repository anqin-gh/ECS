#pragma once
#include <algorithm>
#include <game/cmp/physics.hpp>
#include <game/cmp/render.hpp>
#include "render.hpp"

template<typename GameCTX_t>
RenderSystem_t<GameCTX_t>::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
    , m_framebuffer{std::make_unique<uint32_t[]>(m_w * m_h)}
{
    ptc_open("window", w, h);
}

template<typename GameCTX_t>
RenderSystem_t<GameCTX_t>::~RenderSystem_t() {
    ptc_close();
}

template<typename GameCTX_t>
bool RenderSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const {
    auto screen = m_framebuffer.get();
    auto size = m_w * m_h;
    
    std::fill(screen, screen + size, kR);
    drawAllEntities(ctx);

    ptc_update(screen);

    return !ptc_process_events();
}

template<typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::drawAllEntities(GameCTX_t& ctx) const {
    const auto& renCmps = ctx.template getComponents<RenderComponent_t>();
    for (const auto& ren : renCmps) {
        if (auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(ren))
            renderSpriteWithClipping(ren, *phy);
    }
}

template<typename GameCTX_t>
constexpr void RenderSystem_t<GameCTX_t>::renderSpriteWithClipping(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const noexcept {
   // Drawing coordinates and size
    auto [ x, w, left_off ] = calculateClipping(phy.x, ren.w, m_w);
    auto [ y, h, up_off   ] = calculateClipping(phy.y, ren.h, m_h);

    // Render the entity
    auto getScreenXY = [&](uint32_t x, uint32_t y) { return m_framebuffer.get() + m_w * y + x; };
    auto screen = getScreenXY(x, y);
    auto sprite_it = begin(ren.sprite) + up_off * ren.w + left_off;
    for(uint32_t y = 0; y < h; ++y) {
        for(uint32_t x = 0; x < w; ++x) {
            if (*sprite_it & 0xFF000000)    // Draw only if transparency != 0
                *screen = *sprite_it;
            ++sprite_it;
            ++screen;
        }
        screen += m_w - w;
        sprite_it += ren.w - w;
    }
}

template<typename GameCTX_t>
constexpr auto RenderSystem_t<GameCTX_t>::calculateClipping(uint32_t spritePos, uint32_t size, uint32_t lim) const noexcept {
    uint32_t clippedPos     { spritePos };
    uint32_t clippedSize    { size };
    uint32_t offset         { 0 };

    if (spritePos >= lim) {
        offset = 0 - spritePos;
        if (offset < size) {
            clippedPos = 0;
            clippedSize -= offset;
        }
    } else if (spritePos + size >= lim) {
        uint32_t otherSideOffset = spritePos + size - lim;
        if (otherSideOffset < size)
            clippedSize -= otherSideOffset;
    }

    return std::tuple{ clippedPos, clippedSize, offset };
}

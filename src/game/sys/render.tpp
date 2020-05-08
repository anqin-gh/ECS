#pragma once
#include <algorithm>
#include <game/cmp/debug.hpp>
#include <game/cmp/physics.hpp>
#include <game/cmp/render.hpp>
#include <game/util/colors.hpp>
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
constexpr void
RenderSystem_t<GameCTX_t>::update(GameCTX_t& ctx) const noexcept {
    auto screen = m_framebuffer.get();
    auto size = m_w * m_h;
    
    std::fill(screen, screen + size, colors::kBlack);
    drawAllEntities(ctx);

    if (m_debug) drawDebugData(ctx);

    ptc_update(screen);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawAllEntities(GameCTX_t& ctx) const noexcept {
    for (const auto& ren : ctx.template getComponents<RenderComponent_t>()) {
        if (auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(ren)) {
            renderSpriteWithClipping(ren, *phy);
        }
    }
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::renderSpriteWithClipping(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const noexcept {
   // Drawing coordinates and size
    auto [ x, w, left_off ] = calculateClipping(phy.x, ren.w, m_w);
    auto [ y, h, up_off   ] = calculateClipping(phy.y, ren.h, m_h);

    // Render the entity
    auto* screen = getScreenPos(x, y);
    auto sprite_it = begin(ren.sprite) + up_off * ren.w + left_off;
    for(uint32_t y = 0; y < h; ++y) {
        for(uint32_t x = 0; x < w; ++x) {
            if (*sprite_it & colors::kTransparent)    // Draw only if transparency != 0
                *screen = *sprite_it;
            ++sprite_it;
            ++screen;
        }
        screen += m_w - w;
        sprite_it += ren.w - w;
    }
}

template<typename GameCTX_t>
constexpr auto
RenderSystem_t<GameCTX_t>::calculateClipping(uint32_t pos, uint32_t size, uint32_t lim) const noexcept {
    uint32_t clippedPos     { pos };
    uint32_t clippedSize    { size };
    uint32_t offset         { 0 };

    if (pos >= lim) {                 // Up & left checks
        offset = 0 - pos;
        if (offset < size) {
            clippedPos = 0;
            clippedSize -= offset;
        } else {
            clippedPos = clippedSize = 0;
        }
    } else if (pos + size >= lim) {   // Down & right checks
        uint32_t otherSideOffset = pos + size - lim;
        if (otherSideOffset < size) {
            clippedSize -= otherSideOffset;
        } else {
            clippedPos = clippedSize = 0;
        }
    }

    return std::tuple{ clippedPos, clippedSize, offset };
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawDebugData(const GameCTX_t& ctx) const noexcept {
    for (const auto& dbg : ctx.template getComponents<DebugComponent_t>()) {
        auto* phy = ctx.template getRequiredComponent<PhysicsComponent_t>(dbg);
        auto* col = ctx.template getRequiredComponent<ColliderComponent_t>(dbg);

        if (col && phy) drawBoxTree(col->box, phy->x, phy->y, dbg.color_filling);
    }
}

template<typename GameCTX_t>
constexpr void 
RenderSystem_t<GameCTX_t>::drawBoxTree(const BoundingBoxNode_t& box, uint32_t x, uint32_t y, uint32_t color) const noexcept {
    if (box.collided) drawFullBox(box, x, y, color);
    else              drawBoxLines(box, x, y, color);

    for (const auto& child : box.children)
        drawBoxTree(child, x, y, color >> 1);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawFullBox(const BoundingBoxNode_t& box, uint32_t x, uint32_t y, uint32_t color) const noexcept {
    // Convert to screen coordinates
    auto xl { x + box.box_root.x_left };
    auto xr { x + box.box_root.x_right };
    auto yu { y + box.box_root.y_up };
    auto yd { y + box.box_root.y_down };

    auto [real_x, real_w, off_hori ] = calculateClipping(xl, xr - xl, m_w);
    auto [real_y, real_h, off_vert ] = calculateClipping(yu, yd - yu, m_h);

    drawSquare(real_x, real_y, real_w, real_h, color);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawSquare(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) const noexcept {
    constexpr uint32_t pixel_with{1};

    auto* screen = getScreenPos(x + pixel_with, y + pixel_with);

    for(uint32_t y = 0; y < h - pixel_with; ++y) {
        for (uint32_t x = 0; x < w - pixel_with; ++x) {
            *screen = color;
            ++screen;
        }
        screen += m_w - w + pixel_with;
    }
}

template<typename GameCTX_t>
constexpr void 
RenderSystem_t<GameCTX_t>::drawBoxLines(const BoundingBoxNode_t& box, uint32_t x, uint32_t y, uint32_t color) const noexcept {
    // Convert to screen coordinates
    auto xl { x + box.box_root.x_left };
    auto xr { x + box.box_root.x_right };
    auto yu { y + box.box_root.y_up };
    auto yd { y + box.box_root.y_down };

    drawClippedHorizontalLine(xl, xr, yu, color);
    drawClippedHorizontalLine(xl, xr, yd, color);
    drawClippedVerticalLine  (yu, yd, xl, color);
    drawClippedVerticalLine  (yu, yd, xr, color);

    for (const auto& child : box.children)
        drawBoxLines(child, x, y, color >> 1);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawClippedHorizontalLine(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color) const noexcept {
    auto [ clipped_x, clipped_w, off ] = calculateClipping(x1, x2 - x1, m_w);
    auto* screen = getScreenPos(clipped_x, y);
    drawLine(screen, clipped_w, 1, color);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawClippedVerticalLine(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color) const noexcept {
    auto [ clipped_y, clipped_h, off ] = calculateClipping(y1, y2 - y1, m_h);
    auto* screen = getScreenPos(x, clipped_y);
    drawLine(screen, clipped_h, m_w, color);
}

template<typename GameCTX_t>
constexpr void
RenderSystem_t<GameCTX_t>::drawLine(uint32_t* screen, uint32_t size, uint32_t stride, uint32_t color) const noexcept {
    for (uint32_t i = 0; i < size; ++i) {
        *screen = color;
        screen += stride;
    }
}

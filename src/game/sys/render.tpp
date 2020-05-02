#include <algorithm>

#include <game/sys/render.hpp>

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
void RenderSystem_t<GameCTX_t>::renderSpriteWithClipping(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const {
    auto getScreenXY = [&](uint32_t x, uint32_t y) { return m_framebuffer.get() + m_w * y + x; };

    auto screen = getScreenXY(phy.x, phy.y);
    auto sprite_it = begin(ren.sprite);
    for(uint32_t y = 0; y < ren.h; ++y) {
        for(uint32_t x = 0; x < ren.w; ++x) {
            if (*sprite_it & 0xFF000000)
                *screen = *sprite_it;
            ++sprite_it;
            ++screen;
        }
        screen += m_w - ren.w;
    }
}
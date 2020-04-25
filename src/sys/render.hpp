#pragma once
#include <algorithm>
#include <memory>
#include <cstdint>

#include <cmp/entity.hpp>
#include <util/typealiases.hpp>

namespace ECS {

template<typename GameCTX_t>
struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t w, uint32_t h)
        : m_w{w}, m_h{h}
        , m_framebuffer{std::make_unique<uint32_t[]>(m_w * m_h)}
    {
        ptc_open("window", w, h);
    }

    ~RenderSystem_t() {
        ptc_close();
    }

    void drawAllEntities(GameCTX_t& ctx) const {
        auto screen = m_framebuffer.get();

        auto getScreenXY = [&](uint32_t x, uint32_t y) { return screen + m_w * y + x; };

        auto drawEntity = [&](const auto& ren) {
            if (auto* e = ctx.template getEntityByID(ren.getBelongingEntityID())) {
                if (auto* phy = e->template getComponent<PhysicsComponent_t>()) {
                    auto screen = getScreenXY(phy->x, phy->y);
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
            }
        };
        auto& renCmps = ctx.template getComponents<RenderComponent_t>();
        for_each(begin(renCmps), end(renCmps), drawEntity);
    }

    bool update(GameCTX_t& ctx) const {
        auto screen = m_framebuffer.get();
        auto size = m_w * m_h;
        
        std::fill(screen, screen + size, kR);
        drawAllEntities(ctx);

        ptc_update(screen);

        return !ptc_process_events();
    }

private:
    static constexpr uint32_t kR = 0x00FF0000;
    const uint32_t m_w { 0 }, m_h { 0 };
    UPtr_t<uint32_t[]> m_framebuffer { nullptr };
};

} // namespace ECS

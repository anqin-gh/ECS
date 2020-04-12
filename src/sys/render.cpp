#include <algorithm>

extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <cmp/physics.hpp>
#include <man/entitymanager.hpp>
#include <sys/render.hpp>
#include <util/gamecontext.hpp>

namespace ECS {

RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
    , m_framebuffer{std::make_unique<uint32_t[]>(m_w * m_h)}
{
    ptc_open("window", w, h);
}

RenderSystem_t::~RenderSystem_t() {
    ptc_close();
}

void RenderSystem_t::drawAllEntities(const GameContext_t& ctx) const {
    auto screen = m_framebuffer.get();

    auto getScreenXY = [&](uint32_t x, uint32_t y) { return screen + m_w * y + x; };

    auto drawEntity = [&](const auto& ren) {
        auto ph = ctx.getRequiredPhysicsComponentByEntityID(ren.getBelongingEntityID());
        if(ph) {
            auto screen = getScreenXY(ph->x, ph->y);
            auto sprite_it = begin(ren.sprite);
            for(uint32_t y = 0; y < ren.h; ++y) {
                std::copy(sprite_it, sprite_it + ren.w, screen);
                sprite_it += ren.w;
                screen += m_w;
            }
        }
    };

    for_each(begin(ctx.getRenderComponents()), end(ctx.getRenderComponents()), drawEntity);
}

bool RenderSystem_t::update(const GameContext_t& context) const {
    auto screen = m_framebuffer.get();
    auto size = m_w * m_h;
    
    std::fill(screen, screen + size, kR);
    drawAllEntities(context);

    ptc_update(screen);

    return !ptc_process_events();
}

} // namespace ECS

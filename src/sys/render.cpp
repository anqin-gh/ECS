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

void RenderSystem_t::drawAllEntities(const Vec_t<Entity_t>& entities) const {
    auto screen = m_framebuffer.get();

    auto getScreenXY = [&](uint32_t x, uint32_t y) { return screen + m_w * y + x; };

    auto drawEntity = [&](const Entity_t& e) {
        if(e.phy) {
            auto screen = getScreenXY(e.phy->x, e.phy->y);
            auto sprite_it = begin(e.sprite);
            for(uint32_t y = 0; y < e.h; ++y) {
                std::copy(sprite_it, sprite_it + e.w, screen);
                sprite_it += e.w;
                screen += m_w;
            }
        }
    };

    for_each(begin(entities), end(entities), drawEntity);
}

bool RenderSystem_t::update(const GameContext_t& context) const {
    auto* screen = m_framebuffer.get();
    auto size = m_w * m_h;
    
    std::fill(screen, screen + size, kR);
    drawAllEntities(context.getEntities());

    ptc_update(screen);

    return !ptc_process_events();
}

} // namespace ECS

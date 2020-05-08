#include <fstream>
#include <exception>
#include <tuple>
#include <game/cmp/render.hpp>
#include <picoPNG/src/picopng.hpp>

RenderComponent_t::RenderComponent_t(ECS::EntityID_t eid)
    : ComponentBase_t(eid)
{}

auto RenderComponent_t::loadPNGFileIntoVector(const std::string_view filename) {
    ECS::Vec_t<unsigned char> pixels;
    unsigned long dw, dh;

    std::ifstream file{filename.data(), std::ios::binary};
    if(!file.is_open()) throw std::runtime_error("Wrong path at " + std::string(filename.data())); // TODO: error handling

    ECS::Vec_t<unsigned char> file_vector{
            std::istreambuf_iterator<char>{file}
        ,   std::istreambuf_iterator<char>{}
    };

    decodePNG(pixels, dw, dh, file_vector.data(), file_vector.size());
    return std::tuple{ dw, dh, pixels };
}

void RenderComponent_t::loadFromFile(const std::string_view filename) {
    auto [ dw, dh, pixels ] = loadPNGFileIntoVector(filename);
    w = dw; h = dh;
    initSpriteFromABGRData(pixels);
}

void RenderComponent_t::initSpriteFromABGRData(const ECS::Vec_t<unsigned char>& pixels) {
    sprite.reserve(pixels.size()/4);
    for(auto it = begin(pixels); it != end(pixels); it += 4) {
        uint32_t pixel = 
                    static_cast<uint32_t>(*(it    )) << 16
                |   static_cast<uint32_t>(*(it + 1)) << 8
                |   static_cast<uint32_t>(*(it + 2)) 
                |   static_cast<uint32_t>(*(it + 3)) << 24;
                sprite.push_back(pixel);
    }
}

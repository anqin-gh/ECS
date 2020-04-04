#include <cmp/entity.hpp>

namespace ECS {

Entity_t::Entity_t(uint32_t w_, uint32_t h_)
    : w{w_}, h{h_}
{
    sprite.resize(w * h);
}

Entity_t::Entity_t(std::string filename)
{
    std::vector<unsigned char> pixels {};
    unsigned long dw{0}, dh{0};
    std::ifstream file{filename, std::ios::binary};
    if(!file.is_open()) return;

    std::vector<unsigned char> file_vector{
            std::istreambuf_iterator<char>{file}
        ,   std::istreambuf_iterator<char>{}
    };
    decodePNG(pixels, dw, dh, file_vector.data(), file_vector.size());
    w = dw; h = dh;
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

} // namespace ECS

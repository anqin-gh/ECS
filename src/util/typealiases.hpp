#pragma once
#include <vector>

namespace ECS {
    template<typename T>
    using Vec_t = std::vector<T>;
    using EntityID_t    = std::size_t;
    using ComponentID_t    = std::size_t;
} // namespace ECS

#pragma once
#include <optional>
#include <unordered_map>
#include <vector>

namespace ECS {
    template<typename T>
    using Vec_t = std::vector<T>;

    template<typename T, typename U>
    using UMap_t = std::unordered_map<T, U>;

    template<typename T>
    using Opt_t = std::optional<T>;

    using EntityID_t    = std::size_t;
    using ComponentID_t    = std::size_t;
} // namespace ECS

#pragma once

namespace ECS {

template <typename Container, typename ConstIterator>
constexpr typename Container::iterator remove_constness(Container& c, ConstIterator it) noexcept
{
    return c.erase(it, it);
}

} // namespace ECS

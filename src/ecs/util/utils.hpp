#pragma once

namespace ECS {

template <typename Container, typename ConstIterator>
typename Container::iterator remove_constness(Container& c, ConstIterator it)
{
    return c.erase(it, it);
}

} // namespace ECS

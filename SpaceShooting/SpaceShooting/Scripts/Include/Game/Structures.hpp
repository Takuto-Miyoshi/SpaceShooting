
// 汎用構造体

#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <Game/Concepts.hpp>

namespace game {
    template<concepts::numeric T>
    struct Size {
        using value_type = T;

        value_type Width { value_type() };
        value_type Height { value_type() };
    };
}  // namespace game

#endif  // !STRUCTURES_HPP

// conceptの定義

#ifndef GENERAL_CONCEPTS_H
#define GENERAL_CONCEPTS_H

#include <concepts>

namespace shooting::concepts {
    template<typename T>
    concept arithmetic = std::integral<T> || std::floating_point<T>;

    template<typename T>
    concept not_double = arithmetic<T> && !std::same_as<T, double>;

    template<typename T, typename U>
    concept convertible_or_same_to = std::convertible_to<T, U> || std::same_as<T, U>;
}  // namespace shooting::concepts

#endif  // !GENERAL_CONCEPTS_H

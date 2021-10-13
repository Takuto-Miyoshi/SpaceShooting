// conceptの定義

#ifndef GENERAL_CONCEPTS_H
#define GENERAL_CONCEPTS_H

#include <concepts>

namespace shooting::concepts {
    template<typename T>
    concept number = std::integral<T> || std::floating_point<T>;

    template<typename T>
    concept not_double = number<T> && !std::same_as<T, double>;
}  // namespace shooting::concepts

#endif  // !GENERAL_CONCEPTS_H

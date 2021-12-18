
// 自作コンセプト

#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <concepts>

namespace game::concepts {
    template<typename T>
    /// @brief T型が算術型であることを表す
    /// @note 算術型 = 整数型と不動点少数型とそのcv修飾
    concept numeric = std::is_arithmetic_v<T>;

    template<typename From, typename To>
    /// @brief From型に対してTo型が加算可能であることを表す
    concept add_to = requires( From from, To to ) {
        from + to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型が減算可能であることを表す
    concept subtract_to = requires( From from, To to ) {
        from - to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型が乗算可能であることを表す
    concept multiplication_to = requires( From from, To to ) {
        from* to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型が除算可能であることを表す
    concept division_to = requires( From from, To to ) {
        from / to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型が剰余算可能であることを表す
    concept modulo_to = requires( From from, To to ) {
        from % to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型で左シフト可能であることを表す
    concept left_shift_to = requires( From from, To to ) {
        from << to;
    };

    template<typename From, typename To>
    /// @brief From型に対してTo型で右シフト可能であることを表す
    concept right_shift_to = requires( From from, To to ) {
        from >> to;
    };

    template<typename T>
    /// @brief T型が前置インクリメント可能であることを表す
    concept pre_increment_to = requires( T t ) {
        ++t;
    };

    template<typename T>
    /// @brief T型が後置インクリメント可能であることを表す
    concept post_increment_to = requires( T t ) {
        t++;
    };

    template<typename T>
    /// @brief T型が前置デクリメント可能であることを表す
    concept pre_decrement_to = requires( T t ) {
        --t;
    };

    template<typename T>
    /// @brief T型が後置デクリメント可能であることを表す
    concept post_decrement_to = requires( T t ) {
        t--;
    };

    template<typename T, typename U>
    /// @brief T型がU型に変換可能、または同じ型であることを表す
    concept convertible_or_same_as = std::convertible_to<T, U> || std::same_as<T, U>;
}  // namespace game::concepts

#endif  // !CONCEPTS_HPP


// 汎用関数

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <Game/Concepts.hpp>
#include <random>

namespace game {
    static std::mt19937_64 seed { std::random_device {}() };

    /// @brief min~maxのランダムな整数を取得
    template<std::integral T>
    static constexpr auto Random( const T& min, const T& max ) -> T {
        std::uniform_int_distribution<T> exec { min, max };
        return exec( seed );
    }

    /// @brief -rate~rateのランダムな整数を取得
    template<std::integral T>
    static constexpr auto Random( const T& rate ) -> T {
        std::uniform_int_distribution<T> exec { -rate, rate };
        return exec( seed );
    }

    /// @brief min~maxのランダムな実数を取得
    template<std::floating_point T>
    static constexpr auto Random( const T& min, const T& max ) -> T {
        std::uniform_real_distribution<T> exec { min, max };
        return exec( seed );
    }

    /// @brief -rate~rateのランダムな実数を取得
    template<std::floating_point T>
    static constexpr auto Random( const T& rate ) -> T {
        std::uniform_real_distribution<T> exec { -rate, rate };
        return exec( seed );
    }

}  // namespace game

#endif  // !FUNCTIONS_HPP

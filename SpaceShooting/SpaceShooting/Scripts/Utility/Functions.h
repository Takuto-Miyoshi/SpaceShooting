// 汎用関数

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <random>
#include <string>

#include "../Definition/GeneralConcepts.h"

template<shooting::concepts::convertible_or_same_to<double> T>
constexpr T PI { static_cast<T>( 3.14159 ) };

template<shooting::concepts::convertible_or_same_to<double> T>
constexpr T HALF_PI { static_cast<T>( PI<T> / 2 ) };

template<shooting::concepts::convertible_or_same_to<double> T>
constexpr T TWICE_PI { static_cast<T>( PI<T> * 2 ) };

template<shooting::concepts::convertible_or_same_to<double> T>
constexpr T DELTA { static_cast<T>( 0.000001 ) };

namespace shooting {
    static std::mt19937 seed { std::random_device {}() };

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

    /// @brief fromのpercentage％分を取得
    /// @tparam T 取得する型
    /// @param from 元の値
    /// @param percentage 取得したい割合
    template<concepts::arithmetic T = double>
    static constexpr auto PercentOf( const concepts::arithmetic auto& from, const double& percentage ) noexcept -> T {
        return static_cast<T>( static_cast<double>( from ) * ( percentage / 100.0 ) );
    }

    /// @brief 円に対応したlerp
    /// @param from 元の値
    /// @param to 目標の値
    /// @param percentage 何％目標へ近づけるか @n 1.00 = 100％
    template<concepts::arithmetic T = double>
    static constexpr auto SLerp( const std::convertible_to<double> auto& from, const std::convertible_to<double> auto& to, const double& percentage ) noexcept -> T {
        auto right { static_cast<double>( to ) };
        auto left { static_cast<double>( to ) };
        const auto fromCast { static_cast<double>( from ) };

        // 同じ方向に行く
        ( from < to ) ? (left -= TWICE_PI<double>) : ( right += TWICE_PI<double> );

        const auto leftDistance { abs( left - fromCast ) };
        const auto rightDistance { abs( right - fromCast ) };

        // 移動量の少ない方を使用
        return static_cast<T>( std::lerp( fromCast, ( leftDistance < rightDistance ) ? left : right, percentage ) );
    }

    static constexpr auto EqualString( const std::string& str1, const std::string& str2 ) noexcept -> bool {
        if ( str1.size() != str2.size() ) { return false; }
        return std::equal( str1.begin(), str1.end(), str2.begin(), str2.end(), []( auto& s1, auto& s2 ) { return s1 == s2; } );
    }

    /// @brief ランダムな向きを取得
    /// @return 0 ~ 2PI
    template<std::floating_point T>
    static constexpr auto RandomAngle() -> T {
        return Random<T>( 0.0, TWICE_PI<T> );
    }

    /// @brief 平方根
    template<concepts::arithmetic T>
    static constexpr auto Sqrt( T value ) noexcept -> T {
        if ( value < 0 ) { value = std::negate<T>()( value ); }
        auto half { value / 2 };

        while ( true ) {
            auto e { half * half - value };
            auto t { ( e < 0 ) ? -e : e };
            if ( t < DELTA<double> ) return static_cast<T>( half );
            half -= e / ( half * 2 );
        }
    }
}  // namespace shooting

#endif  // !FUNCTIONS_H

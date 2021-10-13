// 汎用関数

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <random>
#include <string>

#include "../Definition/GeneralConcepts.h"

constexpr double PI { 3.14159 };

namespace shooting {
    static std::mt19937 seed { std::random_device {}() };

    /// @brief min~maxのランダムな整数を取得
    template<concepts::number T>
    static constexpr auto Random( const std::integral auto& min, const std::integral auto& max ) -> T {
        std::uniform_int_distribution<T> exec( min, max );
        return exec( seed );
    }

    /// @brief -rate~rateのランダムな整数を取得
    template<concepts::number T>
    static constexpr auto Random( const std::integral auto& rate ) -> T {
        std::uniform_int_distribution<T> exec( -rate, rate );
        return exec( seed );
    }

    /// @brief min~maxのランダムな実数を取得
    template<concepts::number T>
    static constexpr auto Random( const std::floating_point auto& min, const std::floating_point auto& max ) -> T {
        std::uniform_real_distribution<T> exec( min, max );
        return exec( seed );
    }

    /// @brief -rate~rateのランダムな実数を取得
    template<concepts::number T>
    static constexpr auto Random( const std::floating_point auto& rate ) -> T {
        std::uniform_real_distribution<T> exec( -rate, rate );
        return exec( seed );
    }

    /// @brief fromのpercentage％分を取得
    /// @tparam T 取得する型
    /// @param from 元の値
    /// @param percentage 取得したい割合
    template<concepts::number T = double>
    static constexpr auto PercentOf( const concepts::number auto& from, const double& percentage ) -> T {
        return static_cast<T>( static_cast<double>( from ) * ( percentage / 100.0 ) );
    }

    /// @brief 円に対応したlerp
    /// @param from 元の値
    /// @param to 目標の値
    /// @param percentage 何％目標へ近づけるか @n 1.00 = 100％
    template<concepts::number T = double>
    static constexpr auto SLerp( const concepts::number auto& from, const concepts::number auto& to, const double& percentage ) -> T {
        auto right = static_cast<double>( to );
        auto left = static_cast<double>( to );
        auto fromCast = static_cast<double>( from );

        // 同じ方向に行く
        ( from < to ) ? ( left -= PI * 2 ) : ( right += PI * 2 );

        auto leftDistance = abs( left - fromCast );
        auto rightDistance = abs( right - fromCast );

        // 移動量の少ない方を使用
        return static_cast<T>( std::lerp( fromCast, ( leftDistance < rightDistance ) ? left : right, percentage ) );
    }

    static constexpr auto EqualString( const std::string& str1, const std::string& str2 ) -> bool {
        if ( str1.size() != str2.size() ) { return false; }
        return std::equal( str1.begin(), str1.end(), str2.begin(), str2.end(), []( auto& s1, auto& s2 ) { return s1 == s2; } );
    }
}  // namespace shooting

#endif  // !FUNCTIONS_H

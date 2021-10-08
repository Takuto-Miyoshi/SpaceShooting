// 汎用関数

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <random>
#include <string>

constexpr double PI { 3.14159 };

namespace shooting {
    static std::mt19937 seed { std::random_device {}() };

    /// @brief ランダムな実数を取得
    /// @tparam T 取得する型
    /// @param min 最小値
    /// @param max 最大値
    template<typename T>
    static auto RandomReal( const T& min, const T& max ) -> T {
        std::uniform_real_distribution<T> exec( min, max );
        return exec( seed );
    }

    /// @brief ランダムな実数を取得
    /// @tparam T 取得する型
    /// @param rate 取得する範囲 @n -rate ~ rate
    template<typename T>
    static auto RandomReal( const T& rate ) -> T {
        std::uniform_real_distribution<T> exec( -rate, rate );
        return exec( seed );
    }

    /// @brief ランダムな整数を取得
    /// @tparam T 取得する型
    /// @param min 最小値
    /// @param max 最大値
    template<typename T>
    static auto RandomInt( const T& min, const T& max ) -> T {
        std::uniform_int_distribution<T> exec( min, max );
        return exec( seed );
    }

    /// @brief ランダムな整数を取得
    /// @tparam T 取得する型
    /// @param rate 取得する範囲
    template<typename T>
    static auto RandomInt( const T& rate ) -> T {
        std::uniform_int_distribution<T> exec( -rate, rate );
        return exec( seed );
    }

    /// @brief fromのpercentage％分を取得
    /// @tparam T 取得する型
    /// @param from 元の値
    /// @param percentage 取得したい割合
    template<typename T = double>
    static constexpr auto PercentOf( const T& from, const double& percentage ) {
        return static_cast<T>( static_cast<double>( from ) * ( percentage / 100.0 ) );
    }

    template<typename T = double>
    static auto SLerp( const T& from, const T& to, const double& percentage ) -> T {
        auto right = static_cast<double>( to );
        auto left = static_cast<double>( to );
        auto fromCast = static_cast<double>( from );

        ( from < to ) ? ( left -= PI * 2 ) : ( right += PI * 2 );

        auto leftDistance = abs( left - fromCast );
        auto rightDistance = abs( right - fromCast );

        return static_cast<T>( std::lerp( fromCast, ( leftDistance < rightDistance ) ? left : right, percentage ) );
    }

    static constexpr auto EqualString( const std::string& str1, const std::string& str2 ) -> bool {
        if ( str1.size() != str2.size() ) { return false; }
        return std::equal( str1.begin(), str1.end(), str2.begin(), str2.end(), []( auto& s1, auto& s2 ) { return s1 == s2; } );
    }
}  // namespace shooting

#endif  // !FUNCTIONS_H

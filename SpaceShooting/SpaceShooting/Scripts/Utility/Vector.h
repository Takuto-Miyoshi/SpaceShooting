// ベクトル

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "../Definition/GeneralConcepts.h"
#include "Functions.h"
#include "Property.h"

namespace shooting {
    /// @brief 2次元ベクトル
    struct Vector2 {
       public:
        Vector2() = default;

        /// @brief 2次元ベクトル
        /// @param xValue xの位置
        /// @param yValue yの位置
        explicit Vector2( concepts::number auto&& xValue, concepts::number auto&& yValue ) :
            x( std::move( xValue ) ), y( std::move( yValue ) ) {}

        ~Vector2() = default;

       public:
        /// @brief Vector2{0,0}を取得
        [[nodiscard]] static auto Zero() noexcept -> Vector2 { return Vector2 { 0, 0 }; }

        /// @brief Vector2{0,-1}を取得
        [[nodiscard]] static auto Up() noexcept -> Vector2 { return Vector2 { 0, -1 }; }

        /// @brief Vector2{0,1}を取得
        [[nodiscard]] static auto Down() noexcept -> Vector2 { return Vector2 { 0, 1 }; }

        /// @brief Vector2{1,0}を取得
        [[nodiscard]] static auto Right() noexcept -> Vector2 { return Vector2 { 1, 0 }; }

        /// @brief Vector2{-1,0}を取得
        [[nodiscard]] static auto Left() noexcept -> Vector2 { return Vector2 { -1, 0 }; }

        /// @brief ベクトルの長さを取得
        [[nodiscard]] auto Length() const noexcept -> double { return sqrt( x * x + y * y ); }

        /// @brief 正規化したベクトルを取得
        [[nodiscard]] auto Normalized() const noexcept -> Vector2 { return Vector2 { x / Length(), y / Length() }; }

        /// @brief ターゲットへの2点間のベクトルを取得
        /// @param target ターゲットの位置
        [[nodiscard]] auto To( const Vector2& target ) const noexcept -> Vector2 { return target - *this; }

        /// @brief ターゲットへの向きを取得
        /// @param target ターゲットの位置
        /// @param toUp 上を基準にするか
        [[nodiscard]] auto AngleTo( const Vector2& target, const bool& toUp = true ) const -> float {
            const auto vector { To( target ) };
            const auto radian { static_cast<float>( atan2( vector.y, vector.x ) ) };
            return ( toUp ) ? ( radian + static_cast<float>( PI / 2 ) ) : radian;
        }

        /// @brief ラジアンを単位ベクトルに変換
        [[nodiscard]] static auto FromAngle( const float& angle ) -> Vector2 { return Vector2 { sinf( angle ), -cosf( angle ) }.Normalized(); }

       public:
        auto operator+( const Vector2& vector ) const noexcept -> Vector2 { return Vector2( x + vector.x, y + vector.y ); }

        auto operator-( const Vector2& vector ) const noexcept -> Vector2 { return Vector2( x - vector.x, y - vector.y ); }

        auto operator*( const auto& value ) const noexcept -> Vector2 { return Vector2( x * value, y * value ); }

        auto operator/( const auto& value ) const noexcept -> Vector2 { return Vector2( x / value, y / value ); }

        void operator=( const Vector2& vector ) & noexcept { Set( vector.x, vector.y ); }

        void operator+=( const Vector2& vector ) & noexcept { Set( x + vector.x, y + vector.y ); }

        void operator-=( const Vector2& vector ) & noexcept { Set( x - vector.x, y - vector.y ); }

        void operator*=( const auto& value ) & noexcept { Set( x * value, y * value ); }

        void operator/=( const auto& value ) & noexcept { Set( x / value, y / value ); }

        auto operator==( const Vector2& vector ) const noexcept -> bool { return x == vector.x && y == vector.y; }

        /// @brief 値を設定する @n double
        constexpr void Set( const std::same_as<double> auto& xValue, const std::same_as<double> auto& yValue ) & noexcept {
            x = xValue;
            y = yValue;
        }

        /// @brief 値を設定する @n double以外の数値はキャストされる
        constexpr void Set( const concepts::not_double auto& xValue, const concepts::not_double auto& yValue ) & noexcept {
            x = static_cast<double>( xValue );
            y = static_cast<double>( yValue );
        }

        Property<double> X { x };
        Property<double> Y { y };

       private:
        double x { 0.0 };
        double y { 0.0 };
    };
}  // namespace shooting

#endif  // !VECTOR_H

// ベクトル

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "Property.h"

constexpr double PI { 3.14159 };

namespace shooting {
    /// @brief 2次元ベクトル
    struct Vector2 {
       public:
        Vector2() = default;

        /// @brief 2次元ベクトル
        /// @param xValue xの位置
        /// @param yValue yの位置
        explicit Vector2( auto xValue, auto yValue ) :
            x( xValue ), y( yValue ) {}

        ~Vector2() = default;

       public:
        /// @brief ベクトルの長さを取得
        [[nodiscard]] auto Length() const -> double { return sqrt( x * x + y * y ); }

        /// @brief 正規化したベクトルを取得
        [[nodiscard]] auto Normalized() const -> Vector2 { return Vector2 { x / Length(), y / Length() }; }

        /// @brief ターゲットへの2点間のベクトルを取得
        /// @param target ターゲットの位置
        [[nodiscard]] auto VectorTo( const Vector2 &target ) const -> Vector2 { return target - *this; }

        /// @brief ターゲットへの向きを取得 @n 右が0のラジアン
        /// @param target ターゲットの位置
        /// @param toUp 上を基準にするか
        [[nodiscard]] auto Angle( const Vector2 &target, const bool &toUp = false ) const -> float {
            auto vector = VectorTo( target );
            auto radian = static_cast<float>( atan2( vector.y, vector.x ) );
            return ( toUp ) ? ( radian + static_cast<float>( PI / 2 ) ) : radian;
        }

        /// @brief ラジアンを単位ベクトルに変換
        [[nodiscard]] static auto AngleToVector( const float &angle ) -> Vector2 { return Vector2 { sinf( angle ), -cosf( angle ) }.Normalized(); }

       public:
        auto operator+( const Vector2 &vector ) const -> Vector2 { return Vector2( x + vector.x, y + vector.y ); }

        auto operator-( const Vector2 &vector ) const -> Vector2 { return Vector2( x - vector.x, y - vector.y ); }

        auto operator*( const auto &value ) const -> Vector2 { return Vector2( x * value, y * value ); }

        auto operator/( const auto &value ) const -> Vector2 { return Vector2( x / value, y / value ); }

        void operator=( const Vector2 &vector ) { Set( vector.x, vector.y ); }

        void operator+=( const Vector2 &vector ) { Set( x + vector.x, y + vector.y ); }

        void operator-=( const Vector2 &vector ) { Set( x - vector.x, y - vector.y ); }

        void operator*=( const auto &value ) { Set( x * value, y * value ); }

        void operator/=( const auto &value ) { Set( x / value, y / value ); }

        auto operator==( const Vector2 &vector ) const -> bool { return x == vector.x && y == vector.y; }

        /// @brief 値を設定する
        constexpr void Set( const double &xValue, const double &yValue ) {
            x = xValue;
            y = yValue;
        }

        Property<double> X { x };
        Property<double> Y { y };

       private:
        double x = 0.0;
        double y = 0.0;
    };
}  // namespace shooting

#endif  // !VECTOR_H

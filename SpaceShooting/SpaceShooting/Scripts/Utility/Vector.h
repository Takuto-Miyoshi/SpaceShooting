// ベクトル

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "Property.h"

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
        [[nodiscard]] auto Normalized() const -> Vector2 { return Vector2( x / Length(), y / Length() ); }

        /// @brief ターゲットへの2点間のベクトルを取得
        /// @param target ターゲットの位置
        [[nodiscard]] auto VectorTo( Vector2 target ) const -> Vector2 { return target - *this; }

        /// @brief ターゲットへの向きを取得 @n 右が0のラジアン
        /// @param target ターゲットの位置
        [[nodiscard]] auto Angle( Vector2 target ) const -> double {
            auto vector = VectorTo( target );
            return atan2( vector.x, vector.y );
        }

       public:
        auto operator+( Vector2 vector ) const -> Vector2 { return Vector2( x + vector.x, y + vector.y ); }

        auto operator-( Vector2 vector ) const -> Vector2 { return Vector2( x - vector.x, y - vector.y ); }

        auto operator*( auto value ) const -> Vector2 { return Vector2( x * value, y * value ); }

        auto operator/( auto value ) const -> Vector2 { return Vector2( x / value, y / value ); }

        void operator=( Vector2 vector ) { Set( vector.x, vector.y ); }

        void operator+=( Vector2 vector ) { Set( x + vector.x, y + vector.y ); }

        void operator-=( Vector2 vector ) { Set( x - vector.x, y - vector.y ); }

        void operator*=( auto value ) { Set( x * value, y * value ); }

        void operator/=( auto value ) { Set( x / value, y / value ); }

        auto operator==( Vector2 vector ) const -> bool { return x == vector.x && y == vector.y; }

        /// @brief 値を設定する
        constexpr void Set( double xValue, double yValue ) {
            x = xValue;
            y = yValue;
        }

        Property<double> X { x };
        Property<double> Y { y };

       private:
        double x = 0.0;
        double y = 0.0;
    };

    /// @brief 3次元ベクトル
    struct Vector3 {
       public:
        Vector3() = default;

        /// @brief 3次元ベクトル
        /// @param xValue xの位置
        /// @param yValue yの位置
        /// @param zValue zの位置
        explicit Vector3( auto xValue, auto yValue, auto zValue ) :
            x( xValue ), y( yValue ), z( zValue ) {}

        ~Vector3() = default;

       public:
        /// @brief ベクトルの長さを取得
        [[nodiscard]] auto Length() const -> double { return sqrt( x * x + y * y + z * z ); }

        /// @brief 正規化したベクトルを取得
        [[nodiscard]] auto Normalized() const -> Vector3 { return Vector3( x / Length(), y / Length(), z / Length() ); };

        /// @brief ターゲットへの2点間のベクトルを取得
        /// @param target ターゲットの位置
        [[nodiscard]] auto VectorTo( Vector3 target ) const -> Vector3 { return target - *this; }

       public:
        auto operator+( Vector3 vector ) const -> Vector3 { return Vector3( x + vector.x, y + vector.y, z + vector.z ); }

        auto operator-( Vector3 vector ) const -> Vector3 { return Vector3( x - vector.x, y - vector.y, z - vector.z ); }

        auto operator*( auto value ) const -> Vector3 { return Vector3( x * value, y * value, z * value ); }

        auto operator/( auto value ) const -> Vector3 { return Vector3( x / value, y / value, z * value ); }

        void operator=( Vector3 vector ) { Set( vector.x, vector.y, vector.z ); }

        void operator+=( Vector3 vector ) { Set( x + vector.x, y + vector.y, z + vector.z ); }

        void operator-=( Vector3 vector ) { Set( x - vector.x, y - vector.y, z - vector.z ); }

        void operator*=( auto value ) { Set( x * value, y * value, z * value ); }

        void operator/=( auto value ) { Set( x / value, y / value, z / value ); }

        auto operator==( Vector3 vector ) const -> bool { return x == vector.x && y == vector.y && z == vector.z; }

        /// @brief 値を設定する
        constexpr void Set( double xValue, double yValue, double zValue ) {
            x = xValue;
            y = yValue;
            z = zValue;
        }

        Property<double> X { x };
        Property<double> Y { y };
        Property<double> Z { z };

       private:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };
}  // namespace shooting

#endif  // !VECTOR_H

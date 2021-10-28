
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <compare>
#include <concepts>

#include "../Functions.h"
#include "../Property.hpp"

namespace shooting {
    template<concepts::arithmetic T = double>
    class Vector2 {
       public:
        using default_type = double;
        using value_type = T;
        using const_reference = const value_type&;
        using rvalue_reference = value_type&&;
        using vector_type = Vector2<value_type>;
        using vector_reference = vector_type&;
        using const_vector_reference = const Vector2<value_type>&;
        using rvalue_vector_reference = vector_type&&;

       public:
        Vector2() :
            x( T() ), y( T() ) {
        }

        explicit Vector2( const_reference x_, const_reference y_ ) :
            x( x_ ), y( y_ ) {
        }

        explicit Vector2( rvalue_reference x_, rvalue_reference y_ ) noexcept :
            x( std::move( x_ ) ), y( std::move( y_ ) ) {
        }

        Vector2( const_vector_reference value_ ) :
            x( value_.x ), y( value_.y ) {
        }

        Vector2( rvalue_vector_reference value_ ) noexcept :
            x( std::move( value_.x ) ), y( std::move( value_.y ) ) {
        }

        ~Vector2() = default;

       public:
        /// @brief Vector2<> { 0, 0 }
        template<concepts::arithmetic U = value_type>
        static inline const Vector2<U> Zero = Vector2<U> { 0, 0 };

        /// @brief Vector2<> { 0, -1 }
        template<concepts::arithmetic U = value_type>
        static inline const Vector2<U> Up = Vector2<U> { 0, -1 };

        /// @brief Vector2<> { 0, 1 }
        template<concepts::arithmetic U = value_type>
        static inline const Vector2<U> Down = Vector2<U> { 0, 1 };

        /// @brief Vector2<> { -1, 0 }
        template<concepts::arithmetic U = value_type>
        static inline const Vector2<U> Left = Vector2<U> { -1, 0 };

        /// @brief Vector2<> { 1, 0 }
        template<concepts::arithmetic U = value_type>
        static inline const Vector2<U> Right = Vector2<U> { 1, 0 };

        /// @brief Vector2<> { 0, 0 }からの長さ
        template<concepts::arithmetic U = value_type>
        [[nodiscard]] constexpr auto Length() const noexcept -> U {
            return Sqrt<U>( x * x + y * y );
        }

        /// @brief 長さが1のベクトルに変換する
        template<concepts::arithmetic U = value_type>
        [[nodiscard]] auto Normalized() const noexcept -> Vector2<U> {
            return Vector2<U> { x / Length(), y / Length() };
        }

        /// @brief Vector2<> { -1.0 ~ 1.0, -1.0 ~ 1.0 }を取得
        template<concepts::arithmetic U = default_type>
        [[nodiscard]] static auto RandomUnit() noexcept -> Vector2<U> {
            return Vector2<U> { Random<U>( -1.0, 1.0 ), Random<U>( -1.0, 1.0 ) }.Normalized();
        }

        /// @brief 2点間のベクトルを取得
        [[nodiscard]] auto To( const_vector_reference value ) const noexcept -> vector_type {
            return Vector2( value ) -= *this;
        }

        /// @brief ターゲットへの向きを取得
        /// @param value ターゲットの位置
        /// @param toUp 上を0.0にするか
        /// @return ラジアン角での向き
        template<std::floating_point U = default_type>
        [[nodiscard]] auto AngleTo( const_vector_reference value, const bool& toUp = true ) const -> U {
            auto vector { To( value ).Cast<default_type>() };
            auto radian { atan2( vector.Y, vector.X ) };
            return static_cast<U>( ( toUp ) ? ( radian + (HALF_PI<U>)) : radian );
        }

        /// @brief ラジアン角を単位ベクトルに変換
        template<std::floating_point U = default_type>
        [[nodiscard]] static auto FromAngle( const U& value ) noexcept -> Vector2<U>
        requires std::_Not_same_as<U, float> {
            return Vector2<U> { sin( value ), -cos( value ) }.Normalized();
        }

        /// @brief ラジアン角を単位ベクトルに変換
        template<std::same_as<float> U>
        [[nodiscard]] static auto FromAngle( const U& value ) noexcept -> Vector2<U> {
            return Vector2<U> { sinf( value ), -cosf( value ) }.Normalized();
        }

        /// @brief 単位ベクトルをラジアン角に変換
        template<std::floating_point U = default_type>
        [[nodiscard]] static auto FromUnit( const Vector2<U>& value ) noexcept -> U
            requires std::_Not_same_as<U, float> {
            return atan2( value.y, value.x );
        }

        /// @brief 単位ベクトルをラジアン角に変換
        template<std::same_as<float> U>
        [[nodiscard]] static auto FromUnit( const Vector2<U>& value ) noexcept -> U {
            return atan2f( value.Y, value.X );
        }

       public:
        [[nodiscard]] auto operator+() const noexcept -> vector_type {
            return *this;
        }

        [[nodiscard]] auto operator-() const noexcept -> vector_type {
            return vector_type( -x, -y );
        }

        auto operator+=( const_vector_reference value ) noexcept -> vector_reference {
            x += value.x;
            y += value.y;
            return *this;
        }

        auto operator-=( const_vector_reference value ) noexcept -> vector_reference {
            x -= value.x;
            y -= value.y;
            return *this;
        }

        auto operator*=( const_reference value ) noexcept -> vector_reference {
            x *= value;
            y *= value;
            return *this;
        }

        auto operator/=( const_reference value ) noexcept -> vector_reference {
            x /= value;
            y /= value;
            return *this;
        }

        auto operator=( const_vector_reference value ) & noexcept -> vector_reference {
            x = value.x;
            y = value.y;
            return *this;
        }

        auto operator=( rvalue_vector_reference value ) & noexcept -> vector_reference {
            x = std::move( value.x );
            y = std::move( value.y );
            return *this;
        }

        [[nodiscard]] auto operator+( const_vector_reference value ) noexcept -> vector_type {
            return Vector2<value_type>( *this ) += value;
        }

        [[nodiscard]] auto operator-( const_vector_reference value ) noexcept -> vector_type {
            return Vector2<value_type>( *this ) -= value;
        }

        [[nodiscard]] auto operator*( const_reference value ) noexcept -> vector_type {
            return Vector2( *this ) *= value;
        }

        [[nodiscard]] auto operator/( const_reference value ) noexcept -> vector_type {
            return Vector2( *this ) /= value;
        }

        /// @brief 長さで比較
        [[nodiscard]] auto operator<=>( const_vector_reference value ) const noexcept -> std::partial_ordering {
            return Length() <=> value.Length();
        }

        /// @brief 長さで比較
        [[nodiscard]] auto operator==( const_vector_reference value ) const noexcept -> bool {
            return Length() == value.Length();
        }

       public:
        BasicProperty<value_type> X { x };
        BasicProperty<value_type> Y { y };

        /// @brief セッタ コピー
        constexpr void Set( const value_type& xValue, const value_type& yValue ) noexcept {
            x = xValue;
            y = yValue;
        }

        /// @brief セッタ ムーブ
        constexpr void Set( value_type&& xValue, value_type&& yValue ) noexcept {
            x = std::move( xValue );
            y = std::move( yValue );
        }

        template<concepts::arithmetic U>
        auto Cast() const noexcept -> Vector2<U> {
            return Vector2<U>( static_cast<U>( x ), static_cast<U>( y ) );
        }

       private:
        value_type x;
        value_type y;
    };
}  // namespace shooting

#endif  // !VECTOR2_HPP

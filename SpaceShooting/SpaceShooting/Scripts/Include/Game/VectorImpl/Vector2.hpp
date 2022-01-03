
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <Game/Concepts.hpp>
#include <Game/Property.hpp>
#include <cmath>
#include <format>
#include <numbers>
#include <string>

namespace game {
    template<concepts::numeric T = double>
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
        using string_type = std::string;

       public:
        Vector2() :
            x( value_type() ), y( value_type() ) {
        }

        explicit Vector2( const_reference x_, const_reference y_ ) :
            x( x_ ), y( y_ ) {
        }

        explicit Vector2( rvalue_reference x_, rvalue_reference y_ ) noexcept :
            x( std::move( x_ ) ), y( std::move( y_ ) ) {
        }

        explicit Vector2( const_vector_reference value_ ) :
            x( value_.x ), y( value_.y ) {
        }

        explicit Vector2( rvalue_vector_reference value_ ) noexcept :
            x( std::move( value_.x ) ), y( std::move( value_.y ) ) {
        }

        ~Vector2() = default;

       public:
        /// @brief { 0, 0 }
        [[nodiscard]] static auto Zero() noexcept -> vector_type {
            return vector_type { 0, 0 };
        }

        /// @brief { 0, -1 }
        [[nodiscard]] static auto Up() noexcept -> vector_type {
            return vector_type { 0, -1 };
        }

        /// @brief { 0, 1 }
        [[nodiscard]] static auto Down() noexcept -> vector_type {
            return vector_type { 0, 1 };
        }

        /// @brief { -1, 0 }
        [[nodiscard]] static auto Left() noexcept -> vector_type {
            return vector_type { -1, 0 };
        }

        /// @brief { 1, 0 }
        [[nodiscard]] static auto Right() noexcept -> vector_type {
            return vector_type { 1, 0 };
        }

        /// @brief { 0, 0 }からの長さ
        template<concepts::numeric U = value_type>
        [[nodiscard]] constexpr auto Length() const noexcept -> U {
            return static_cast<U>( sqrt( x * x + y * y ) );
        }

        /// @brief 長さが1のベクトルに変換する
        template<concepts::numeric U = value_type>
        [[nodiscard]] auto Normalized() const noexcept -> Vector2<U> {
            return Vector2<U> { *this / Length() };
        }

        /// @brief 2点間のベクトルを取得
        [[nodiscard]] auto To( const_vector_reference value_ ) const noexcept -> vector_type {
            return Vector2( value_ ) -= *this;
        }

        /// @brief targetとの距離を取得
        template<concepts::numeric U = value_type>
        [[nodiscard]] auto Distance( const_vector_reference target_ ) const noexcept -> U {
            return To( target_ ).Length();
        }

        /// @brief ターゲットへの向きを取得
        /// @param value_ ターゲットの位置
        /// @param toUp_ 上を0.0にするか
        /// @return ラジアン角での向き
        template<std::floating_point U = default_type>
        [[nodiscard]] auto AngleTo( const_vector_reference value_, const bool& toUp_ = true ) const -> U {
            auto vector { To( value_ ).Cast<default_type>() };
            auto radian { atan2( vector.Y, vector.X ) };
            return static_cast<U>( ( toUp_ ) ? ( radian + ( std::numbers::pi_v<U> / 2 ) ) : radian );
        }

        /// @brief 全要素を出力に適した文字列に変換する
        [[nodiscard]] auto ToString() const -> string_type {
            return std::format( "x: {} | y: {}", x, y );
        }

        /// @brief ラジアン角を単位ベクトルに変換
        template<std::floating_point U = default_type>
        [[nodiscard]] static auto FromAngle( const U& value_ ) noexcept -> Vector2<U>
        requires std::_Not_same_as<U, float> {
            return Vector2<U> { sin( value_ ), -cos( value_ ) }.Normalized();
        }

        /// @brief ラジアン角を単位ベクトルに変換
        template<std::same_as<float> U>
        [[nodiscard]] static auto FromAngle( const U& value_ ) noexcept -> Vector2<U> {
            return Vector2<U> { sinf( value_ ), -cosf( value_ ) }.Normalized();
        }

        /// @brief 単位ベクトルをラジアン角に変換
        template<std::floating_point U = default_type>
        [[nodiscard]] static auto ToAngle( const Vector2<U>& value_ ) noexcept -> U
            requires std::_Not_same_as<U, float> {
            return atan2( value_.y, value_.x );
        }

        /// @brief 単位ベクトルをラジアン角に変換
        template<std::same_as<float> U>
        [[nodiscard]] static auto ToAngle( const Vector2<U>& value_ ) noexcept -> U {
            return atan2f( value_.Y, value_.X );
        }

       public:
        [[nodiscard]] auto operator+() const noexcept -> vector_type {
            return *this;
        }

        [[nodiscard]] auto operator-() const noexcept -> vector_type {
            return vector_type( -x, -y );
        }

        auto operator+=( const_vector_reference value_ ) noexcept -> vector_reference {
            x += value_.x;
            y += value_.y;
            return *this;
        }

        auto operator-=( const_vector_reference value_ ) noexcept -> vector_reference {
            x -= value_.x;
            y -= value_.y;
            return *this;
        }

        auto operator*=( const_reference value_ ) noexcept -> vector_reference {
            x *= value_;
            y *= value_;
            return *this;
        }

        auto operator/=( const_reference value_ ) noexcept -> vector_reference {
            x /= value_;
            y /= value_;
            return *this;
        }

        auto operator=( const_vector_reference value_ ) & noexcept -> vector_reference {
            x = value_.x;
            y = value_.y;
            return *this;
        }

        auto operator=( rvalue_vector_reference value_ ) & noexcept -> vector_reference {
            x = std::move( value_.x );
            y = std::move( value_.y );
            return *this;
        }

        [[nodiscard]] auto operator+( const_vector_reference value_ ) noexcept -> vector_type {
            return vector_type( *this ) += value_;
        }

        [[nodiscard]] auto operator-( const_vector_reference value_ ) noexcept -> vector_type {
            return vector_type( *this ) -= value_;
        }

        [[nodiscard]] auto operator*( const_reference value_ ) noexcept -> vector_type {
            return vector_type( *this ) *= value_;
        }

        [[nodiscard]] auto operator/( const_reference value_ ) noexcept -> vector_type {
            return vector_type( *this ) /= value_;
        }

        /// @brief 長さで比較
        [[nodiscard]] auto operator<=>( const_vector_reference value_ ) const noexcept -> std::partial_ordering {
            return Length() <=> value_.Length();
        }

        /// @brief 1e-5未満の誤差は許容
        [[nodiscard]] auto operator==( const_vector_reference value_ ) const noexcept -> bool {
            auto diff { abs( x - value_.x ) + abs( y - value_.y ) };
            return diff < 1e-5;
        }

       public:
        BasicProperty<value_type> X { x };
        BasicProperty<value_type> Y { y };

        /// @brief セッタ コピー
        constexpr void Set( const_reference x_, const_reference y_ ) & noexcept {
            x = x_;
            y = y_;
        }

        /// @brief セッタ ムーブ
        constexpr void Set( rvalue_reference x_, rvalue_reference y_ ) & noexcept {
            x = std::move( x_ );
            y = std::move( y_ );
        }

        template<std::convertible_to<value_type> U>
        auto Cast() const noexcept -> Vector2<U> {
            return Vector2<U> { static_cast<U>( x ), static_cast<U>( y ) };
        }

       private:
        value_type x;
        value_type y;
    };
}  // namespace game

#endif  // !VECTOR2_HPP

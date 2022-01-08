
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <Game/Accessor.hpp>
#include <Game/Functions.hpp>
#include <Game/Mathematics.hpp>
#include <format>

namespace game {
    class Vector2 {
       public:
        using value_type = double;
        using const_reference = const value_type&;
        using rvalue_reference = value_type&&;

        using vector_reference = Vector2&;
        using const_vector_reference = const Vector2&;
        using rvalue_vector_reference = Vector2&&;

       public:
        constexpr Vector2() = default;

        explicit constexpr Vector2( const_reference xValue, const_reference yValue ) noexcept :
            x { xValue }, y { yValue } {
        }

        explicit constexpr Vector2( rvalue_reference xValue, rvalue_reference yValue ) noexcept :
            x { std::move( xValue ) }, y { std::move( yValue ) } {
        }

        ~Vector2() = default;

       public:
        /// @brief Vector2 { 0.0, 0.0 } を取得
        [[nodiscard]] static constexpr auto Zero() noexcept -> Vector2 {
            return Vector2 { 0.0, 0.0 };
        }

        /// @brief Vector2 { 0.0, -1.0 } を取得
        [[nodiscard]] static constexpr auto Up() noexcept -> Vector2 {
            return Vector2 { 0.0, -1.0 };
        }

        /// @brief Vector2 { 0.0, 1.0 } を取得
        [[nodiscard]] static constexpr auto Down() noexcept -> Vector2 {
            return Vector2 { 0.0, 1.0 };
        }

        /// @brief Vector2 { -1.0, 0.0 } を取得
        [[nodiscard]] static constexpr auto Left() noexcept -> Vector2 {
            return Vector2 { -1.0, 0.0 };
        }

        /// @brief Vector2 { 1.0, 0.0 } を取得
        [[nodiscard]] static constexpr auto Right() noexcept -> Vector2 {
            return Vector2 { 1.0, 0.0 };
        }

        /// @brief Vector2 { -1.0 ~ 1.0, -1.0 ~ 1.0 } を取得
        [[nodiscard]] static constexpr auto RandomUnit() -> Vector2 {
            return Vector2 { Random<value_type>( 1.0 ), Random<value_type>( 1.0 ) };
        }

        /// @brief Vector2 { 0.0, 0.0 } からの距離を取得
        [[nodiscard]] constexpr auto Length() const noexcept -> value_type {
            return Sqrt<value_type>( x * x + y * y );
        }

        /// @brief 長さが1のベクトルに変換する
        [[nodiscard]] constexpr auto Normalized() const noexcept -> Vector2 {
            return Vector2 { x / Length(), y / Length() };
        }

        /// @brief 2点間のベクトルを取得する
        [[nodiscard]] constexpr auto To( const_vector_reference value ) const noexcept -> Vector2 {
            return Vector2 { value } -= *this;
        }

        /// @brief パラメータとの距離を取得する
        [[nodiscard]] constexpr auto Distance( const_vector_reference value ) const noexcept -> value_type {
            return To( value ).Length();
        }

        /// @brief パラメータの方向を向く @n ベクトル角への使用を想定
        constexpr void LookTo( const_vector_reference value ) noexcept {
            *this = To( value ).Normalized();
        }

        /// @brief パラメータへの角度を取得する
        /// @param toUp 上を0.0度にするか
        [[nodiscard]] constexpr auto AngleTo( const_vector_reference value, const bool& toUp = true ) const noexcept -> value_type {
            auto vec { To( value ) };
            auto rad { Atan2( vec.x, vec.y ) };
            return ( toUp ) ? rad + ( std::numbers::pi_v<value_type> / 2 ) : rad;
        }

        /// @brief ラジアン角をベクトル角に変換する
        [[nodiscard]] static constexpr auto ToUnit( const_reference value ) noexcept -> Vector2 {
            return Vector2 { Sin( value ), -Cos( value ) }.Normalized();
        }

        /// @brief ベクトル角をラジアン角に変換する
        [[nodiscard]] static constexpr auto ToAngle( const_vector_reference value ) noexcept -> value_type {
            return Atan2( value.x, value.y );
        }

       public:
        [[nodiscard]] constexpr auto operator+() const noexcept -> Vector2 {
            return Vector2 { x, y };
        }

        [[nodiscard]] constexpr auto operator-() const noexcept -> Vector2 {
            return Vector2 { -x, -y };
        }

        constexpr auto operator+=( const_vector_reference value ) noexcept -> vector_reference {
            x += value.x;
            y += value.y;
            return *this;
        }

        constexpr auto operator-=( const_vector_reference value ) noexcept -> vector_reference {
            x -= value.x;
            y -= value.y;
            return *this;
        }

        constexpr auto operator*=( const_reference value ) noexcept -> vector_reference {
            x *= value;
            y *= value;
            return *this;
        }

        constexpr auto operator/=( const_reference value ) noexcept -> vector_reference {
            x /= value;
            y /= value;
            return *this;
        }

        /// @brief 1e-5未満の誤差は許容
        constexpr auto operator==( const_vector_reference value ) const noexcept -> bool {
            auto diff { Abs( x - value.x ) + Abs( y - value.y ) };
            return diff < 1e-5;
        }

        /// @brief 長さで比較
        constexpr auto operator<=>( const_vector_reference value ) const noexcept -> std::partial_ordering {
            return Length() <=> value.Length();
        }

       public:
        Accessor<value_type> X { x };
        Accessor<value_type> Y { y };

        constexpr void Set( const_reference xValue, const_reference yValue ) noexcept {
            x = xValue;
            y = yValue;
        }

        constexpr void Set( rvalue_reference xValue, rvalue_reference yValue ) noexcept {
            x = std::move( xValue );
            y = std::move( yValue );
        }

       private:
        value_type x { value_type() };
        value_type y { value_type() };
    };

    /// @brief 出力用の文字列を生成する
    [[nodiscard]] inline auto ToString( const Vector2& value ) noexcept -> std::string {
        return std::format( "X : {:.4} | Y : {:.4}", value.X(), value.Y() );
    }

    constexpr auto operator+( const Vector2& valueA, const Vector2& valueB ) noexcept -> Vector2 {
        return Vector2 { valueA } += valueB;
    }

    constexpr auto operator-( const Vector2& valueA, const Vector2& valueB ) noexcept -> Vector2 {
        return Vector2 { valueA } -= valueB;
    }

    constexpr auto operator*( const Vector2& vector, Vector2::const_reference value ) noexcept -> Vector2 {
        return Vector2 { vector } *= value;
    }

    constexpr auto operator/( const Vector2& vector, Vector2::const_reference value ) noexcept -> Vector2 {
        return Vector2 { vector } /= value;
    }
}  // namespace game

#endif  // !VECTOR2_HPP

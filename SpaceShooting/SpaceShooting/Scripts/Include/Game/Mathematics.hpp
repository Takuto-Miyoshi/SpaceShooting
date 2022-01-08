
// 定数式の数学関数

#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

#include <Game/Concepts.hpp>
#include <limits>
#include <numbers>

namespace game {
    template<concepts::numeric T>
    static constexpr auto Abs( const T& value ) noexcept -> T;

    namespace {
        template<std::floating_point T>
        [[nodiscard]] static constexpr auto SqrtImpl( const T& value, const T& current, const T& previous ) noexcept -> T {
            return ( current == previous ) ? current : SqrtImpl( value, 0.5 * ( current + value / current ), current );
        }

        template<std::floating_point T>
        static constexpr auto Feq( const T& x, const T& y ) noexcept -> bool {
            return Abs( x - y ) <= std::numeric_limits<T>::epsilon();
        }

        template<std::floating_point T>
        [[nodiscard]] static constexpr auto TrigSeries( const T& value, const T& sum, const T& n, const int32_t& i, const int32_t& s, const T& t ) noexcept -> T {
            return ( Feq( sum, value + t * s / n ) ) ? sum : TrigSeries( value, sum + t * s / n, n * i * ( i + 1 ), i + 2, -s, t * value * value );
        }

        template<std::floating_point T>
        [[nodiscard]] static constexpr auto AtanTerm( const T& value, const int32_t& k ) noexcept -> T {
            return ( 2.0 * static_cast<T>( k ) * value ) / ( ( 2.0 * static_cast<T>( k ) + 1.0 ) * ( 1.0 + value ) );
        }

        template<std::floating_point T>
        [[nodiscard]] static constexpr auto AtanProduct( const T& value, const int& k ) noexcept -> T {
            return ( k == 1 ) ? AtanTerm( value * value, k ) : AtanTerm( value * value, k ) * AtanProduct( value, k - 1 );
        }

        template<std::floating_point T>
        [[nodiscard]] static constexpr auto AtanSum( const T& value, const T& sum, const int& n ) noexcept -> T {
            return ( sum + AtanProduct( value, n ) == sum ) ? sum : AtanSum( value, sum + AtanProduct( value, n ), n + 1 );
        }
    }  // namespace

    /// @brief 平方根
    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Sqrt( const T& value ) noexcept -> T {
        return ( value >= 0.0 && value < std::numeric_limits<T>::infinity() ) ? SqrtImpl( value, value, 0.0 ) : std::numeric_limits<T>::quiet_NaN();
    }

    /// @brief 絶対値
    template<concepts::numeric T>
    [[nodiscard]] static constexpr auto Abs( const T& value ) noexcept -> T {
        return ( value >= 0.0 ) ? value : -value;
    }

    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Sin( const T& value ) noexcept -> T {
        return TrigSeries( value, value, 6.0, 4, -1, value * value * value );
    }

    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Cos( const T& value ) noexcept -> T {
        return TrigSeries( value, 1.0, 2.0, 3, -1, value * value );
    }

    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Tan( const T& value ) noexcept -> T {
        return ( Cos( value ) != 0.0 ) ? Sin( value ) / Cos( value ) : std::numeric_limits<T>::quiet_NaN();
    }

    /// @brief 逆正接
    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Atan( const T& value ) noexcept -> T {
        return value / ( 1.0 + value * value ) * AtanSum( value, 1.0, 1 );
    }

    /// @brief 対辺と隣辺から求める逆正接
    template<std::floating_point T>
    [[nodiscard]] static constexpr auto Atan2( const T& x, const T& y ) noexcept -> T {
        return ( x > 0.0 )               ? Atan( y / x )
               : ( y >= 0.0 && x < 0.0 ) ? Atan( y / x ) + std::numbers::pi_v<T>
               : ( y < 0.0 && x < 0.0 )  ? Atan( y / x ) - std::numbers::pi_v<T>
               : ( y > 0.0 && x == 0.0 ) ? std::numbers::pi_v<T> / 2.0
               : ( y < 0.0 && x == 0.0 ) ? -std::numbers::pi_v<T> / 2.0
                                         : std::numeric_limits<T>::quiet_NaN();
    }
}  // namespace game

#endif  // !MATHEMATICS_HPP

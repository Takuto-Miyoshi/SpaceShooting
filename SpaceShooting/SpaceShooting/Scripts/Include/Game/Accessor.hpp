
// アクセサ

#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include <concepts>
#include <type_traits>

namespace game {
    template<typename T>
    class Accessor {
       public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using rvalue_reference = value_type&&;
        using arrow_type = T*;

       public:
        constexpr Accessor() = default;

        explicit constexpr Accessor( reference value ) :
            base { value } {
        }

        ~Accessor() = default;

       public:
        [[nodiscard]] constexpr auto operator()() const noexcept -> const_reference {
            return base.get();
        }

        [[nodiscard]] constexpr auto operator->() const noexcept -> arrow_type {
            return base.get();
        }

        constexpr void operator()( const_reference value ) noexcept {
            base = value;
        }

        constexpr void operator()( rvalue_reference value ) noexcept {
            base = std::move( value );
        }

        constexpr void Add( const_reference value ) noexcept {
            base.get() += value;
        }

        template<std::convertible_to<value_type> U>
        [[nodiscard]] constexpr auto Cast() const -> U {
            return static_cast<U>( base.get() );
        }

       private:
        std::reference_wrapper<value_type> base {};
    };

    template<typename T>
    class Reader {
       public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using arrow_type = const T*;

       public:
        constexpr Reader() = default;

        explicit constexpr Reader( reference value ) :
            base { value } {
        }

        ~Reader() = default;

       public:
        [[nodiscard]] constexpr auto operator()() const noexcept -> const_reference {
            return base.get();
        }

        [[nodiscard]] constexpr auto operator->() const noexcept -> arrow_type {
            return base.get();
        }

        template<std::convertible_to<value_type> U>
        [[nodiscard]] constexpr auto Cast() const -> U {
            return static_cast<U>( base.get() );
        }

       private:
        std::reference_wrapper<value_type> base {};
    };
}  // namespace game

#endif  // !ACCESSOR_HPP

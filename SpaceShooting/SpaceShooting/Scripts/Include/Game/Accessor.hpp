
// 外部からのアクセサ

#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include <type_traits>

namespace game {
    template<typename T>
    class Accessor {
       public:
        using value_type = T;

       public:
        struct Get {
           public:
            using get_type = const value_type&;
            using get_reference = value_type&;

           public:
            explicit constexpr Get( value_type& value ) :
                data { value } {
            }

            ~Get() = default;

            [[nodiscard]] constexpr auto operator()() const -> get_type {
                return data;
            }

           private:
            value_type& data;
        };

        struct Set {
           public:
            using set_type = const value_type&;
            using set_move = value_type&&;

           public:
            explicit constexpr Set( value_type& value ) :
                data { value } {
            }

            ~Set() = default;

            constexpr void operator()( set_type value ) & {
                data = value;
            }

            constexpr void operator()( set_move value ) & {
                data = std::move( value );
            }

           private:
            value_type& data;
        };

       public:
        explicit constexpr Accessor( T& value ) :
            get { value }, set { value } {
        }

        ~Accessor() = default;

       public:
        [[nodiscard]] constexpr auto operator()() -> decltype( auto ) {
            return get();
        }

        constexpr void operator()( auto&& value ) {
            set( value );
        }

       private:
        Get get;
        Set set;
    };

}  // namespace game

#endif  // !ACCESSOR_HPP

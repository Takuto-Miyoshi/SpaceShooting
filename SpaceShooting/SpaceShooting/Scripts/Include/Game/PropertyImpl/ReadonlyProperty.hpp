
#ifndef READONLY_PROPERTY_HPP
#define READONLY_PROPERTY_HPP

#include <Game/Concepts.hpp>
#include <functional>

namespace game {
    template<typename T>
    class ReadonlyProperty {
       public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using index_type = const uint64_t&;

       public:
        /// @brief プロパティ
        /// @param target プロパティを適用する変数
        /// @param getter ゲッターのオーバーライド
        /// @param setter セッターのオーバーライド
        explicit ReadonlyProperty( reference target, std::function<value_type()>&& getter = nullptr ) noexcept :
            base( target ), get( std::move( getter ) ) {
        }

        ~ReadonlyProperty() = default;

       public:
        [[nodiscard]] constexpr operator value_type() const {
            return Get();
        }

        /// @brief 変換可能な値にキャスト
        template<std::convertible_to<value_type> U>
        [[nodiscard]] constexpr auto Cast() const noexcept -> U {
            return static_cast<U>( base );
        }

        /// @brief メンバ選択演算子
        constexpr auto operator->() const -> decltype( auto ) {
            return &base;
        }

        /// @brief 添字演算子
        /// @note 基本的には .at() などのメンバ関数を使うべき
        template<typename U = value_type>
        constexpr auto operator[]( index_type index ) const -> decltype( std::declval<U>()[std::declval<index_type>()] ) {
            return base[index];
        }

        /// @brief 論理否定演算子
        [[nodiscard]] constexpr auto operator!() const -> bool requires std::convertible_to<bool, value_type> {
            return !static_cast<bool>( base );
        }

        /// @brief 単項プラス演算子
        template<concepts::numeric U = value_type>
        constexpr auto operator+() const noexcept -> value_type {
            return *this;
        }

        /// @brief 単項マイナス演算子
        template<concepts::numeric U = value_type>
        constexpr auto operator-() const -> value_type {
            return std::negate()( base );
        }

        /// @brief 関節参照演算子
        [[nodiscard]] constexpr auto operator*() const noexcept -> value_type {
            return base;
        }

        [[nodiscard]] constexpr auto Get() const -> value_type {
            return ( get ) ? get() : base;
        }

       private:
        const_reference base;
        std::function<value_type()> get { nullptr };
    };  // namespace shooting
}  // namespace game

#endif  // !READONLY_PROPERTY

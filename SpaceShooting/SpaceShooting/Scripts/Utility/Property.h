// プロパティ的なアクセサ

#ifndef PROPERTY_H
#define PROPERTY_H

#include <functional>
#include <memory>

// ゲッターメソッド
#define Getter( method ) [this]() { method }

// セッターメソッド
#define Setter( value, method ) [this]( value ) { method }

namespace shooting {
    template<typename T>
    class Property {
       public:
        /// @brief プロパティ
        /// @param target プロパティを適用する変数
        /// @param getter ゲッターのオーバーライド
        /// @param setter セッターのオーバーライド
        explicit Property( T& target, std::function<T()> getter = nullptr, std::function<void( T )> setter = nullptr ) :
            base( target ), get( std::move( getter ) ), set( std::move( setter ) ) {}

        ~Property() = default;

       public:
        operator T() const {
            return ( get ) ? get() : base;
        }

        void operator=( const T value ) {
            if ( set ) { set( value ); }
            else {
                base = value;
            }
        }

        void operator=( const Property<T> value ) {
            if ( set ) { set( value.base ); }
            else {
                base = value.base;
            }
        }

        void operator+=( const T value ) {
            if ( set ) { set( base + value ); }
            else {
                base += value;
            }
        }

        void operator+=( const Property<T> value ) {
            if ( set ) { set( base + value.base ); }
            else {
                base += value.base;
            }
        }

        void operator-=( const T value ) {
            if ( set ) { set( base - value ); }
            else {
                base -= value;
            }
        }

        void operator-=( const Property<T> value ) {
            if ( set ) { set( base - value.base ); }
            else {
                base -= value.base;
            }
        }

        auto operator+( T& right ) -> T { return base + right; }

        auto operator-( T& right ) -> T { return base - right; }

        auto operator*( T& right ) -> T { return base * right; }

        auto operator/( T& right ) -> T { return base / right; }

        auto operator+( Property<T>& right ) -> T { return base + right; }

        auto operator-( Property<T>& right ) -> T { return base - right; }

        auto operator*( Property<T>& right ) -> T { return base * right; }

        auto operator/( Property<T>& right ) -> T { return base / right; }

        auto operator->() const -> T* { return &base; }

        auto operator&() const -> T* { return &base; }

       private:
        T& base;
        std::function<T()> get = nullptr;
        std::function<void( T )> set = nullptr;
    };

    template<typename T>
    class ReadonlyProperty {
       public:
        /// @brief 読み取り専用プロパティ
        /// @param target プロパティを適用する変数
        /// @param getter ゲッターのオーバーライド
        explicit ReadonlyProperty( T& target, std::function<T()> getter = nullptr ) :
            base( target ), get( std::move( getter ) ) {}

        ~ReadonlyProperty() = default;

       public:
        operator T() const {
            return ( get ) ? get() : base;
        }

        auto operator+( T& right ) -> T { return base + right; }

        auto operator-( T& right ) -> T { return base - right; }

        auto operator*( T& right ) -> T { return base * right; }

        auto operator/( T& right ) -> T { return base / right; }

        auto operator+( ReadonlyProperty<T>& right ) -> T { return base + right; }

        auto operator-( ReadonlyProperty<T>& right ) -> T { return base - right; }

        auto operator*( ReadonlyProperty<T>& right ) -> T { return base * right; }

        auto operator/( ReadonlyProperty<T>& right ) -> T { return base / right; }

        auto operator->() const -> T* { return &base; }

        auto operator&() const -> T* { return &base; }

       private:
        T& base;
        std::function<T()> get = nullptr;
    };

    template<typename T>
    class SmartProperty {
       public:
        /// @brief スマートポインタ(weak_ptr)用プロパティ
        /// @param target プロパティを適用するスマートポインタ(weak_ptr)
        /// @param getter ゲッターのオーバーライド
        explicit SmartProperty( std::weak_ptr<T> target, std::function<std::weak_ptr<T>()> getter = nullptr ) :
            base( target ), get( getter ) {}

        /// @brief スマートポインタ(weak_ptr)用プロパティ
        /// @param target プロパティを適用するスマートポインタ(shared_ptr)
        /// @param getter ゲッターのオーバーライド
        explicit SmartProperty( std::shared_ptr<T> target, std::function<std::weak_ptr<T>()> getter = nullptr ) :
            base( target ), get( getter ) {}

        ~SmartProperty() = default;

       public:
        operator std::weak_ptr<T>() const {
            if ( get ) {
                std::weak_ptr<T> returns = get();
                if ( returns.expired() ) {
                    throw std::exception( "参照先が見つかりません" );
                }

                return returns;
            }
            else {
                if ( base.expired() ) {
                    throw std::exception( "参照先が見つかりません" );
                }

                return base;
            }
        }

        auto operator->() const -> T* { return base.lock().get(); }

       private:
        std::weak_ptr<T> base;
        std::function<std::weak_ptr<T>()> get = nullptr;
    };
}  // namespace shooting

#endif  // !PROPERTY_H

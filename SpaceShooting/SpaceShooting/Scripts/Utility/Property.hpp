
#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "Property/BasicProperty.hpp"
#include "Property/ReadonlyProperty.hpp"

namespace shooting {
    // +

    template<typename T, typename U>
    auto operator+( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return *lvalue + *rvalue;
    }

    template<typename T, typename U>
    auto operator+( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return *lvalue + *rvalue;
    }

    template<typename T, typename U>
    auto operator+( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return *lvalue + *rvalue;
    }

    template<typename T, typename U>
    auto operator+( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return *lvalue + *rvalue;
    }

    template<typename T, typename U>
    auto operator+( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return *lvalue + rvalue;
    }

    template<typename T, typename U>
    auto operator+( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() + std::declval<U>() ) {
        return lvalue + *rvalue;
    }

    // -

    template<typename T, typename U>
    auto operator-( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return *lvalue - *rvalue;
    }

    template<typename T, typename U>
    auto operator-( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return *lvalue - *rvalue;
    }

    template<typename T, typename U>
    auto operator-( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return *lvalue - *rvalue;
    }

    template<typename T, typename U>
    auto operator-( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return *lvalue - *rvalue;
    }

    template<typename T, typename U>
    auto operator-( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return *lvalue - rvalue;
    }

    template<typename T, typename U>
    auto operator-( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() - std::declval<U>() ) {
        return lvalue - *rvalue;
    }

    // *

    template<typename T, typename U>
    auto operator*( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return *lvalue * *rvalue;
    }

    template<typename T, typename U>
    auto operator*( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return *lvalue * *rvalue;
    }

    template<typename T, typename U>
    auto operator*( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return *lvalue * *rvalue;
    }

    template<typename T, typename U>
    auto operator*( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return *lvalue * *rvalue;
    }

    template<typename T, typename U>
    auto operator*( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return *lvalue * rvalue;
    }

    template<typename T, typename U>
    auto operator*( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() * std::declval<U>() ) {
        return lvalue * *rvalue;
    }

    // /

    template<typename T, typename U>
    auto operator/( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return *lvalue / *rvalue;
    }

    template<typename T, typename U>
    auto operator/( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return *lvalue / *rvalue;
    }

    template<typename T, typename U>
    auto operator/( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return *lvalue / *rvalue;
    }

    template<typename T, typename U>
    auto operator/( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return *lvalue / *rvalue;
    }

    template<typename T, typename U>
    auto operator/( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return *lvalue / rvalue;
    }

    template<typename T, typename U>
    auto operator/( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() / std::declval<U>() ) {
        return lvalue / *rvalue;
    }

    // %

    template<typename T, typename U>
    auto operator%( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return *lvalue % *rvalue;
    }

    template<typename T, typename U>
    auto operator%( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return *lvalue % *rvalue;
    }

    template<typename T, typename U>
    auto operator%( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return *lvalue % *rvalue;
    }

    template<typename T, typename U>
    auto operator%( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return *lvalue % *rvalue;
    }

    template<typename T, typename U>
    auto operator%( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return *lvalue % rvalue;
    }

    template<typename T, typename U>
    auto operator%( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() % std::declval<U>() ) {
        return lvalue % *rvalue;
    }

    // <<

    template<typename T, typename U>
    auto operator<<( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return *lvalue << *rvalue;
    }

    template<typename T, typename U>
    auto operator<<( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return *lvalue << *rvalue;
    }

    template<typename T, typename U>
    auto operator<<( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return *lvalue << *rvalue;
    }

    template<typename T, typename U>
    auto operator<<( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return *lvalue << *rvalue;
    }

    template<typename T, typename U>
    auto operator<<( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return *lvalue << rvalue;
    }

    template<typename T, typename U>
    auto operator<<( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() << std::declval<U>() ) {
        return lvalue << *rvalue;
    }

    // >>

    template<typename T, typename U>
    auto operator>>( const BasicProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return *lvalue >> *rvalue;
    }

    template<typename T, typename U>
    auto operator>>( const BasicProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return *lvalue >> *rvalue;
    }

    template<typename T, typename U>
    auto operator>>( const ReadonlyProperty<T>& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return *lvalue >> *rvalue;
    }

    template<typename T, typename U>
    auto operator>>( const ReadonlyProperty<T>& lvalue, const ReadonlyProperty<U>& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return *lvalue >> *rvalue;
    }

    template<typename T, typename U>
    auto operator>>( const BasicProperty<T>& lvalue, const U& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return *lvalue >> rvalue;
    }

    template<typename T, typename U>
    auto operator>>( const T& lvalue, const BasicProperty<U>& rvalue ) -> decltype( std::declval<T>() >> std::declval<U>() ) {
        return lvalue >> *rvalue;
    }

}  // namespace shooting

#endif  // !PROPERTY_HPP

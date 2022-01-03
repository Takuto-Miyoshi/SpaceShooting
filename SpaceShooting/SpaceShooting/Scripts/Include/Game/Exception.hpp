
// 自作例外クラス

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

namespace game::exception {
    /// @brief 初期化時のエラー
    class InitializeError : public std::runtime_error {
       public:
        InitializeError( const char* message = nullptr ) :
            runtime_error( ( message ) ? message : "初期化に失敗しました。" ) {
        }

        InitializeError( std::string_view message ) :
            runtime_error( message.data() ) {
        }

        ~InitializeError() = default;
    };

    /// @brief 見つかりませんでした。なエラー
    class NotFound : public std::runtime_error {
       public:
        NotFound( const char* message = nullptr ) :
            runtime_error( ( message ) ? message : "見つかりませんでした。" ) {
        }

        NotFound( std::string_view message ) :
            runtime_error( message.data() ) {
        }

        ~NotFound() = default;
    };
}  // namespace game::exception

#endif  // !EXCEPTION_HPP

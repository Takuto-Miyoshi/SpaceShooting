
// 特定のキーが押されたときに関数を呼び出す

#ifndef INPUT_INVOKER_HPP
#define INPUT_INVOKER_HPP

#include <Game/Enums.hpp>
#include <Game/Singleton.hpp>
#include <functional>
#include <map>

namespace game {
    class InputInvoker : public Singleton<InputInvoker> {
       public:
        struct InvokeData {
            int32_t KeyId;
            std::function<void( const InputState& )> Method;
        };

        struct InvokeSpec {
            int32_t KeyId;
            InputState State;
            std::function<void()> Method;
        };

       public:
        InputInvoker() = default;

        ~InputInvoker() override = default;

       public:
        /// @brief キーがInputState::None以外の時に引数を伴って呼ばれる関数を登録
        /// @param name 登録名
        /// @param data 呼び出しデータ
        void Regist( std::string_view name, const InvokeData& data );

        /// @brief キーが特定の状態の時に呼び出される関数を登録
        /// @param name 登録名
        /// @param data 呼び出しデータ
        void Regist( std::string_view name, const InvokeSpec& data );

        /// @brief 登録した関数を削除
        /// @param name 登録名
        void Unregist( std::string_view name ) noexcept;

        /// @brief 更新
        void Update();

       private:
        std::multimap<std::string, InvokeData> list {};
        std::multimap<std::string, InvokeSpec> listSpec {};
    };
}  // namespace game

#endif  // !INPUT_INVOKER_HPP

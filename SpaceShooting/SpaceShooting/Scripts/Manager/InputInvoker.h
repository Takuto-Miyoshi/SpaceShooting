// 入力に応じて関数を呼び出す

#ifndef INPUT_INVOKER_H
#define INPUT_INVOKER_H

#include <array>
#include <functional>
#include <vector>

#include "../Definition/InputDefinition.h"
#include "../Utility/Singleton.h"

namespace shooting {
    class InputInvoker : public Singleton<InputInvoker> {
       public:
        /// @brief InputInvokerへの登録名
        enum class Target {
            None,
            Player,
        };

       private:
        struct RegistData {
            std::function<void( InputState )> function;  // 実行する関数
            Target target;  // 登録名
        };

       public:
        InputInvoker() = default;

        ~InputInvoker() = default;

       public:
        void Initialize();

        void Update();

        /// @brief 呼び出す関数を登録(キー)
        /// @param id キーID @n KEY_INPUT_XXXX
        /// @param function 呼び出す関数
        void RegisterKey( const int32_t& id, std::function<void( InputState )>&& function, Target&& target = Target::None ) {
            keyFunctions.at( id ).push_back( { std::move( function ), target } );
        }

        /// @brief 特定のキーに登録された関数をリセット
        void UnregisterKey( const int32_t& id ) {
            keyFunctions.at( id ).clear();
        }

        /// @brief 呼び出す関数を登録(マウスボタン)
        /// @param id マウスボタンID @n MOUSEBUTTON_XXXX
        /// @param function 呼び出す関数
        void RegisterMousebutton( const int32_t& id, std::function<void( InputState )>&& function, Target&& target = Target::None ) {
            mousebuttonFunctions.at( id ).push_back( { std::move( function ), target } );
        }

        /// @brief 特定のマウスボタンに登録された関数をリセット
        void UnregisterMousebutton( const int32_t& id ) {
            mousebuttonFunctions.at( id ).clear();
        }

        /// @brief 特定のターゲットに登録された関数をリセット
        void UnregisterTarget( Target&& target );

        /// @brief 登録した関数を全てリセット
        void Reset() noexcept;

       private:
        // 登録された関数を保存(Key)
        /// @note (キー)<(関数)<(型)>>
        std::array<std::vector<RegistData>, NUMBER_OF_KEY> keyFunctions {};

        // 登録された関数を保存(MB)
        /// @note (マウスボタン)<(関数)<(型)>>
        std::array<std::vector<RegistData>, NUMBER_OF_MOUSEBUTTON> mousebuttonFunctions {};
    };
}  // namespace shooting

#endif  // !INPUT_INVOKER_H

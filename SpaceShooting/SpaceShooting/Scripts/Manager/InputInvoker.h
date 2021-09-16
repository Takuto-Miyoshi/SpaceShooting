// 入力に応じて関数を呼び出す

#ifndef INPUT_INVOKER_H
#define INPUT_INVOKER_H

#include <functional>
#include <vector>

#include "../Definition/InputDefinition.h"
#include "../Utility/Singleton.h"

namespace shooting {
    class InputInvoker : public Singleton<InputInvoker> {
       public:
        InputInvoker() = default;

        ~InputInvoker() = default;

       public:
        void Initialize();

        void Update();

        /// @brief 呼び出す関数を登録(キー)
        /// @param id キーID @n KEY_INPUT_XXXX
        /// @param function 呼び出す関数
        void RegisterKey( const int32_t& id, std::function<void( InputState )>&& function ) {
            keyFunctions.at( id ).push_back( std::move( function ) );
        }

        /// @brief 呼び出す関数を登録(マウスボタン)
        /// @param id マウスボタンID @n MOUSEBUTTON_XXXX
        /// @param function 呼び出す関数
        void RegisterMousebutton( const int32_t& id, std::function<void( InputState )>&& function ) {
            mousebuttonFunctions.at( id ).push_back( std::move( function ) );
        }

        /// @brief 登録した関数を全てリセット
        void Reset();

       private:
        // 登録された関数を保存(Key) @n (キー)<(関数)<(型)>>
        std::vector<std::vector<std::function<void( InputState )>>> keyFunctions { NUMBER_OF_KEY };

        // 登録された関数を保存(MB) @n (マウスボタン)<(関数)<(型)>>
        std::vector<std::vector<std::function<void( InputState )>>> mousebuttonFunctions { NUMBER_OF_MOUSEBUTTON };
    };
}  // namespace shooting

#endif  // !INPUT_INVOKER_H

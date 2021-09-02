#include "InputInvoker.h"

#include <algorithm>

#include "InputManager.h"

namespace shooting {
    void InputInvoker::Initialize() {
        keyFunctions = std::vector<std::vector<std::function<void( InputState )>>>( NUMBER_OF_KEY );
        mousebuttonFunctions = std::vector<std::vector<std::function<void( InputState )>>>( NUMBER_OF_MOUSEBUTTON );
    }

    void InputInvoker::Update() {
        uint32_t i = 0;
        // キー入力
        std::for_each( keyFunctions.begin(), keyFunctions.end(), [&i]( auto& key ) {
            if ( !key.empty() ) {
                std::for_each( key.begin(), key.end(), [&i]( auto& function ) {
                    // キーに登録された関数を実行
                    function( InputManager::Instance().lock()->KeyState( i ) );
                } );
            }
            // 次のキー
            i++;
        } );

        i = 0;
        // マウス入力
        std::for_each( mousebuttonFunctions.begin(), mousebuttonFunctions.end(), [&i]( auto& mousebutton ) {
            if ( !mousebutton.empty() ) {
                std::for_each( mousebutton.begin(), mousebutton.end(), [&i]( auto& function ) {
                    function( InputManager::Instance().lock()->MousebuttonState( i ) );
                } );
            }

            i++;
        } );
    }
}  // namespace shooting

#include "InputInvoker.h"

#include <algorithm>

#include "InputManager.h"

namespace shooting {
    void InputInvoker::Initialize() {
        for ( auto& element : keyFunctions ) {
            element.reserve( input::FUNCTION_CAPACITY );
        }

        for ( auto& element : mousebuttonFunctions ) {
            element.reserve( input::FUNCTION_CAPACITY );
        }
    }

    void InputInvoker::Update() {
        uint32_t i = 0;
        // キー入力
        for ( auto&& key : std::as_const( keyFunctions ) ) {
            if ( !key.empty() ) {
                for ( auto&& function : key ) {
                    function( InputManager::Instance()->KeyState( i ) );
                }
            }
            i++;
        }

        i = 0;
        // マウス入力
        for ( auto&& mousebutton : std::as_const( mousebuttonFunctions ) ) {
            if ( !mousebutton.empty() ) {
                for ( auto&& function : mousebutton ) {
                    function( InputManager::Instance()->MousebuttonState( i ) );
                }
            }
            i++;
        }
    }

    void InputInvoker::Reset() {
        for ( auto& element : keyFunctions ) {
            element.clear();
        }

        for ( auto& element : mousebuttonFunctions ) {
            element.clear();
        }
    }
}  // namespace shooting

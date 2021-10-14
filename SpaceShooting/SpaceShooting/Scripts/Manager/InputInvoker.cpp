#include "InputInvoker.h"

#include <algorithm>

#include "InputManager.h"

namespace shooting {
    void InputInvoker::Initialize() {
        for ( auto&& element : keyFunctions ) {
            element.reserve( input::FUNCTION_CAPACITY );
        }

        for ( auto&& element : mousebuttonFunctions ) {
            element.reserve( input::FUNCTION_CAPACITY );
        }
    }

    void InputInvoker::Update() {
        // キー入力
        for ( auto i { 0u };
              auto&& key : std::as_const( keyFunctions ) ) {
            if ( !key.empty() ) {
                for ( auto&& element : key ) {
                    element.function( InputManager::Instance()->KeyState( i ) );
                }
            }
            i++;
        }

        // マウス入力
        for ( auto i { 0u };
              auto&& mousebutton : std::as_const( mousebuttonFunctions ) ) {
            if ( !mousebutton.empty() ) {
                for ( auto&& element : mousebutton ) {
                    element.function( InputManager::Instance()->MousebuttonState( i ) );
                }
            }
            i++;
        }
    }

    void InputInvoker::UnregisterTarget( Target&& target ) {
        for ( auto&& key : keyFunctions ) {
            if ( !key.empty() ) {
                std::erase_if( key, [&target]( const auto& element ) {
                    return element.target == target;
                } );
            }
        }

        for ( auto&& mousebutton : mousebuttonFunctions ) {
            if ( !mousebutton.empty() ) {
                std::erase_if( mousebutton, [&target]( const auto& element ) {
                    return element.target == target;
                } );
            }
        }
    }

    void InputInvoker::Reset() noexcept {
        for ( auto&& element : keyFunctions ) {
            element.clear();
        }

        for ( auto&& element : mousebuttonFunctions ) {
            element.clear();
        }
    }
}  // namespace shooting

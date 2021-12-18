

#include <DxLib.h>

#include <Game/InputManager.hpp>

namespace game {
    InputManager::InputManager() {
        keyList.fill( InputState::None );
        mousebuttonList.fill( InputState::None );
    }

    void InputManager::Update() & noexcept {
        UpdateKeyState();
        UpdateMousebutton();
        UpdateCursorPosition();
    }

    constexpr auto InputManager::ConvertState( const InputState& previous, const bool& current ) noexcept -> InputState {
        if ( previous == InputState::Pressed || previous == InputState::Hold ) {
            return ( current ) ? InputState::Hold : InputState::Released;
        }
        else {
            return ( current ) ? InputState::Pressed : InputState::None;
        }
    }

    constexpr void InputManager::UpdateKeyState() noexcept {
        for ( auto index { 0u };
              auto&& key : keyList ) {
            key = ConvertState( key, CheckHitKey( index ) == DX_PRESSED );
            index++;
        }
    }

    constexpr void InputManager::UpdateMousebutton() noexcept {
        for ( auto index { MOUSE_INPUT_LEFT };
              auto&& mousebutton : mousebuttonList ) {
            mousebutton = ConvertState( mousebutton, ( GetMouseInput() & index ) != DX_NOT_PRESSED );
            index <<= 1;
        }
    }

    void InputManager::UpdateCursorPosition() noexcept {
        auto x { 0 }, y { 0 };
        GetMousePoint( &x, &y );
        cursorPosition.Set( static_cast<double>( x ), static_cast<double>( y ) );
    }
}  // namespace game

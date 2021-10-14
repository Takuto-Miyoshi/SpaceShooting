#include "InputManager.h"

#include <algorithm>

#include "DxLib.h"

namespace shooting {
    InputManager::InputManager() {
        previousKeys.fill( false );
        keyStates.fill( InputState::None );
        previousMousebuttons.fill( false );
        mousebuttonStates.fill( InputState::None );
    }

    void InputManager::Update() {
        UpdateKeyState();

        UpdateMousebuttonState();

        UpdateCursorPosition();
    }

    constexpr auto InputManager::ConvertToState( const bool& current, const bool& previous ) noexcept -> InputState {
        if ( current ) {
            return ( previous ) ? InputState::Hold : InputState::Pressed;
        }

        return ( previous ) ? InputState::Released : InputState::None;
    }

    void InputManager::UpdateKeyState() noexcept {
        std::array<bool, NUMBER_OF_KEY> currentKeys;
        // 入力状態を取得
        for ( auto i { 0u };
              auto&& element : currentKeys ) {
            element = CheckHitKey( i );
            i++;
        }

        for ( auto current { currentKeys.begin() }, previous { previousKeys.begin() };
              auto &&key : keyStates ) {
            // 入力状態へ変換
            key = ConvertToState( *current, *previous );

            // 前回の状態を更新
            *previous = *current;

            // 次の要素へ
            current++;
            previous++;
        }
    }

    void InputManager::UpdateMousebuttonState() noexcept {
        auto previous { previousMousebuttons.begin() };
        for ( auto numButton { MOUSE_INPUT_LEFT };
              auto&& mousebutton : mousebuttonStates ) {
            // 入力状態を取得
            auto current { ( GetMouseInput() & numButton ) != dxlib::NOT_PRESSED };

            // 入力状態へ変換
            mousebutton = ConvertToState( current, *previous );

            *previous = current;

            // 次の要素へ
            previous++;
            numButton = numButton << 1;
        }
    }

    void InputManager::UpdateCursorPosition() noexcept {
        auto x { 0 }, y { 0 };
        GetMousePoint( &x, &y );
        cursorPosition.Set( x, y );
    }
}  // namespace shooting

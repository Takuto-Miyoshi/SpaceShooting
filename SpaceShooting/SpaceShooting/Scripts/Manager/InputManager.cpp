#include "InputManager.h"

#include <algorithm>
#include <array>

#include "DxLib.h"

namespace shooting {
    void InputManager::Update() {
        UpdateKeyState();

        UpdateMousebuttonState();

        UpdateCursorPosition();
    }

    constexpr auto InputManager::ConvertToState( const bool& current, const bool& previous ) -> InputState {
        if ( current ) {
            return ( previous ) ? InputState::Hold : InputState::Pressed;
        }

        return ( previous ) ? InputState::Released : InputState::None;
    }

    void InputManager::UpdateKeyState() {
        std::array<char, NUMBER_OF_KEY> currentKeys;
        // 入力状態を取得
        GetHitKeyStateAll( currentKeys.data() );

        auto current = currentKeys.begin();
        auto previous = previousKeys.begin();
        for ( auto& key : keyStates ) {
            // 入力状態へ変換
            key = ConvertToState( *current == dxlib::PRESSED, *previous );

            // 前回の状態を更新
            *previous = *current;

            // 次の要素へ
            current++;
            previous++;
        }
    }

    void InputManager::UpdateMousebuttonState() {
        auto previous = previousMousebuttons.begin();
        auto numButton = MOUSE_INPUT_LEFT;  // 左ボタンから調べる
        for ( auto& mousebutton : mousebuttonStates ) {
            // 入力状態を取得
            auto current = ( GetMouseInput() & numButton ) != dxlib::NOT_PRESSED;

            // 入力状態へ変換
            mousebutton = ConvertToState( current, *previous );

            *previous = current;

            // 次の要素へ
            previous++;
            numButton = numButton << 1;
        }
    }

    void InputManager::UpdateCursorPosition() {
        int32_t x = 0;
        int32_t y = 0;
        GetMousePoint( &x, &y );
        cursorPosition.Set( x, y );
    }
}  // namespace shooting

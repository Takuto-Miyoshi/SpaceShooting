#include "InputManager.h"

#include <algorithm>
#include <array>

#include "../Definition/InputDefinition.h"
#include "DxLib.h"

namespace shooting {
    void InputManager::Initialize() {
        previousKeys = std::vector<bool>( NUMBER_OF_KEY, false );
        keyStates = std::vector<InputState>( NUMBER_OF_KEY, InputState::None );

        previousMousebuttons = std::vector<bool>( NUMBER_OF_MOUSEBUTTON, false );
        mousebuttonStates = std::vector<InputState>( NUMBER_OF_MOUSEBUTTON, InputState::None );
    }

    void InputManager::Update() {
        UpdateKeyState();

        UpdateMousebuttonState();

        // カーソル位置
        int32_t x = 0;
        int32_t y = 0;
        GetMousePoint( &x, &y );
        cursorPosition.Set( x, y );
    }

    constexpr auto InputManager::ConvertToState( bool current, bool previous ) -> InputState {
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
        std::for_each( keyStates.begin(), keyStates.end(), [&current, &previous]( auto& element ) {
            // 入力状態へ変換
            element = ConvertToState( *current == DxLib::PRESSED, *previous );

            // 前回の状態を更新
            *previous = *current;

            // 次の要素へ
            current++;
            previous++;
        } );
    }

    void InputManager::UpdateMousebuttonState() {
        auto previous = previousMousebuttons.begin();
        auto numButton = MOUSE_INPUT_LEFT;  // 左ボタンから調べる
        std::for_each( mousebuttonStates.begin(), mousebuttonStates.end(), [&numButton, &previous]( auto& element ) {
            // 入力状態を取得
            auto current = ( GetMouseInput() & numButton ) != DxLib::NOT_PRESSED;

            // 入力状態へ変換
            element = ConvertToState( current, *previous );

            *previous = current;

            // 次の要素へ
            previous++;
            numButton = numButton << 1;
        } );
    }
}  // namespace shooting

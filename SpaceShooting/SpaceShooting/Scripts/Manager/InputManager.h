// 入力状態を詳細に記録

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>

#include "../Definition/InputDefinition.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.h"

namespace shooting {
    class InputManager : public Singleton<InputManager> {
       public:
        InputManager() = default;

        ~InputManager() = default;

       public:
        /// @brief 更新
        void Update();

       private:
        /// @brief InputStateへ変換
        [[nodiscard]] static constexpr auto ConvertToState( const bool& current, const bool& previous ) -> InputState;

        /// @brief キーの入力状態を更新
        void UpdateKeyState();

        /// @brief マウスボタンの入力状態を更新
        void UpdateMousebuttonState();

        /// @brief カーソル位置情報を更新
        void UpdateCursorPosition();

       public:
        /// @brief キーの入力状態を取得
        /// @param id キーID @n KEY_INPUT_XXXX
        [[nodiscard]] constexpr auto KeyState( const uint32_t& id ) const -> InputState { return keyStates.at( id ); }

        /// @brief マウスボタンの入力状態を取得
        /// @param id マウスボタンID @n shooting::MOUSEBUTTON_XXXX
        [[nodiscard]] constexpr auto MousebuttonState( const uint32_t& id ) const -> InputState { return mousebuttonStates.at( id ); }

        /// @brief マウスの位置
        ReadonlyProperty<Vector2> CursorPosition { cursorPosition };

       private:
        std::vector<bool> previousKeys { std::vector<bool>( NUMBER_OF_KEY, false ) };
        std::vector<InputState> keyStates { std::vector<InputState>( NUMBER_OF_KEY, InputState::None ) };

        std::vector<bool> previousMousebuttons { std::vector<bool>( NUMBER_OF_MOUSEBUTTON, false ) };
        std::vector<InputState> mousebuttonStates { std::vector<InputState>( NUMBER_OF_MOUSEBUTTON, InputState::None ) };
        Vector2 cursorPosition;
    };
}  // namespace shooting

#endif  // !INPUT_MANAGER_H

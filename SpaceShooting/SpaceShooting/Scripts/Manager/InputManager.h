// 入力状態を詳細に記録

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <array>
#include <vector>

#include "../Definition/InputDefinition.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.hpp"

namespace shooting {
    class InputManager : public Singleton<InputManager> {
       public:
        InputManager();

        ~InputManager() = default;

       public:
        /// @brief 更新
        void Update();

       private:
        /// @brief InputStateへ変換
        [[nodiscard]] static constexpr auto ConvertToState( const bool& current, const bool& previous ) noexcept -> InputState;

        /// @brief キーの入力状態を更新
        void UpdateKeyState() noexcept;

        /// @brief マウスボタンの入力状態を更新
        void UpdateMousebuttonState() noexcept;

        /// @brief カーソル位置情報を更新
        void UpdateCursorPosition() noexcept;

       public:
        /// @brief キーの入力状態を取得
        /// @param id キーID @n KEY_INPUT_XXXX
        [[nodiscard]] constexpr auto KeyState( const uint32_t& id ) const -> const InputState& { return keyStates.at( id ); }

        /// @brief マウスボタンの入力状態を取得
        /// @param id マウスボタンID @n shooting::MOUSEBUTTON_XXXX
        [[nodiscard]] constexpr auto MousebuttonState( const uint32_t& id ) const -> const InputState& { return mousebuttonStates.at( id ); }

        /// @brief マウスの位置
        ReadonlyProperty<Vector2<double>> CursorPosition { cursorPosition };

       private:
        std::array<bool, NUMBER_OF_KEY> previousKeys {};
        std::array<InputState, NUMBER_OF_KEY> keyStates {};

        std::array<bool, NUMBER_OF_MOUSEBUTTON> previousMousebuttons {};
        std::array<InputState, NUMBER_OF_MOUSEBUTTON> mousebuttonStates {};

        Vector2<double> cursorPosition;
    };
}  // namespace shooting

#endif  // !INPUT_MANAGER_H

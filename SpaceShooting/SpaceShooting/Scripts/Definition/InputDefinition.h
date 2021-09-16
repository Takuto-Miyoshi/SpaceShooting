// 入力に関する定義

#ifndef INPUT_DEFINITION_H
#define INPUT_DEFINITION_H

#include <cstdint>

namespace shooting {
    /// @brief 入力状態
    enum class InputState {
        None,  // 入力なし
        Pressed,  // 押された瞬間
        Hold,  // 押されている
        Released,  // 離された瞬間
    };

    /// @brief キーの数
    constexpr uint32_t NUMBER_OF_KEY { 256 };

    /// @brief マウスボタンの数
    constexpr uint32_t NUMBER_OF_MOUSEBUTTON { 3 };
    /// @brief マウスボタン左
    constexpr uint32_t MOUSEBUTTON_LEFT { 0 };
    /// @brief マウスボタン右
    constexpr uint32_t MOUSEBUTTON_RIGHT { 1 };
    /// @brief マウスボタンホイール
    constexpr uint32_t MOUSEBUTTON_WHEEL { 2 };

    namespace input {
        constexpr uint32_t FUNCTION_CAPACITY { 10 };
    }

    /// @brief DxLib用の定義
    namespace dxlib {
        /// @brief 押している状態
        constexpr int32_t PRESSED { 1 };
        /// @brief 押していない状態
        constexpr int32_t NOT_PRESSED { 0 };
    }  // namespace dxlib
}  // namespace shooting

#endif  // !INPUT_DEFINITION_H

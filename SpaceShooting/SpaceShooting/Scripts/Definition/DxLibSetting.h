// DxLibの設定に用いる値を定義

#ifndef DX_LIB_SETTING_H
#define DX_LIB_SETTING_H

#include <cstdint>
#include <string>

namespace shooting::DxLib {
    constexpr int32_t FAIL { -1 };

    constexpr int32_t SCREEN_SIZE_X { 1280 };
    constexpr int32_t SCREEN_SIZE_Y { 720 };
    constexpr int32_t COLOR_BIT_DEPTH { 32 };

    const std::string WINDOW_NAME { "Shooting" };
}  // namespace shooting::DxLib

#endif  // !DX_LIB_SETTING_H

// 汎用関数

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <random>

namespace shooting {
    std::mt19937 seed { std::random_device {}() };

    /// @brief float型のランダムな値を取得
    /// @param min 最小値
    /// @param max 最大値
    auto RandomFloat( float min, float max ) -> float {
        std::uniform_real_distribution<float> exec( min, max );
        return exec( seed );
    }

    /// @brief float型のランダムな値を取得
    /// @param rate 範囲 @n (-rate ~ rate)
    auto RandomFloat( float rate ) -> float {
        std::uniform_real_distribution<float> exec( -rate, rate );
        return exec( seed );
    }
}  // namespace shooting

#endif  // !FUNCTIONS_H

// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

#include <cstdint>

namespace shooting::object {
    constexpr uint32_t OBJECT_CAPACITY { 500 };

    namespace status {
        enum class ObjectKind {
            Player,
            PlayerBullet,
            Enemy,
            EnemyBullet
        };

        enum class BulletType {
            StandardBullet,
        };

        namespace player {
            constexpr double SPEED { 120.0 };
            constexpr double COLLISION_RADIUS { 32.0 };
        }  // namespace player

        namespace enemy {
            constexpr double COLLISION_RADIUS { 16.0 };
        }

        /// @brief 弾が消えるまでの時間
        constexpr double LIFE_SPAN_OF_BULLET { 5.0 };

        namespace standardBullet {
            constexpr double SPEED { 150.0 };
            constexpr double COLLISION_RADIUS { 8.0 };
        }  // namespace standardBullet
    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

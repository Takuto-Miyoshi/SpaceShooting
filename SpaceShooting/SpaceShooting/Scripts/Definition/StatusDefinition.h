// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

#include <cstdint>

namespace shooting::object {
    constexpr uint32_t OBJECT_CAPACITY { 300 };

    namespace status {
        enum class BulletType {
            StandardBullet,
        };

        namespace player {
            constexpr double SPEED { 120.0 };
        }

        namespace standardBullet {
            constexpr double SPEED { 150.0 };
        }
    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

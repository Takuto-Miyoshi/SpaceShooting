// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

namespace shooting::object::status {
    enum class BulletType {
        StandardBullet,
    };

    namespace player {
        constexpr double SPEED = 120.0;
    }

    namespace standardBullet {
        constexpr double SPEED = 150.0;
    }
}  // namespace shooting::object::status

#endif  // !STATUS_DEFINITION_H

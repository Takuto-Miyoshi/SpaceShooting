// 自動追尾弾

#ifndef HOMING_BULLET_H
#define HOMING_BULLET_H

#include "BulletBase.h"

namespace shooting::object {
    class HomingBullet : public BulletBase {
       public:
        HomingBullet() = default;

        ~HomingBullet() override = default;

       protected:
        void Start() override;

        void Move() override;

       private:
        auto TargetPosition() const -> Vector2;
    };
}  // namespace shooting::object

#endif  // !HOMING_BULLET_H

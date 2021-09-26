// 直進する弾

#ifndef STANDARD_BULLET_H
#define STANDARD_BULLET_H

#include "BulletBase.h"

namespace shooting::object {
    class StandardBullet : public BulletBase {
       public:
        StandardBullet() = default;

        ~StandardBullet() override = default;

       protected:
        void Start() override;

        void Move() override;
    };
}  // namespace shooting::object

#endif  // !STANDARD_BULLET_H

// 直進する弾

#ifndef STANDARD_BULLET_H
#define STANDARD_BULLET_H

#include "BulletBase.h"

namespace shooting::object {
    class StandardBullet : public BulletBase {
       public:
        StandardBullet() = default;

        ~StandardBullet() override = default;

       public:
        void Start() override {
            speed = status::standardBullet::SPEED;
            graphicHandle = ImageManager::Instance().lock()->Image( image::standardBullet.name );

            update = { [this] {
                position += Vector2::AngleToVector( angle ) * speed * timeManager.lock()->DeltaTime;
            } };
        }

       private:
    };
}  // namespace shooting::object

#endif  // !STANDARD_BULLET_H

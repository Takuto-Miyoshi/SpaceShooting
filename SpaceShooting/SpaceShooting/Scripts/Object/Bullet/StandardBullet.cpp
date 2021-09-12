#include "StandardBullet.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void StandardBullet::Start() {
        speed = status::StandardBullet::SPEED;
        graphicHandle = ImageManager::Instance()->Image( image::STANDARD_BULLET.name );
        collisionRadius = status::StandardBullet::COLLISION_RADIUS;
        attackPower = status::StandardBullet::ATTACK_POWER;
    }

    void StandardBullet::Update() {
        BulletBase::Update();
        position += Vector2::AngleToVector( angle ) * speed * timeManager.lock()->DeltaTime;
    }
}  // namespace shooting::object

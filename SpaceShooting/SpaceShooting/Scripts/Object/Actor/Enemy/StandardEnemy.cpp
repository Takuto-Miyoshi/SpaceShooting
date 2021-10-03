#include "StandardEnemy.h"

#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"

namespace shooting::object {
    void StandardEnemy::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::STANDARD_ENEMY.name );

        objectStatus = status::enemy::StandardEnemy::OBJECT;
        actorStatus = status::enemy::StandardEnemy::ACTOR;
    }

    void StandardEnemy::Update() {
        Shoot();
        Move();
    }

    void StandardEnemy::Move() {
        angle += timeManager.lock()->DeltaTime;
        MoveToForward();
    }

    void StandardEnemy::Shoot() {
        shotCount += timeManager.lock()->DeltaTime;
        if ( shotCount >= status::enemy::StandardEnemy::SHOT_INTERVAL ) {
            shotCount = 0;

            float shootAngle = position.AngleTo( ObjectManager::Instance()->PlayerPosition() );
            object::BulletFactory::Instance()->Create( status::ObjectKind::EnemyBullet,
                                                       status::bullet::Type::StandardBullet,
                                                       position,
                                                       shootAngle,
                                                       status::enemy::StandardEnemy::BULLET );
        }
    }
}  // namespace shooting::object

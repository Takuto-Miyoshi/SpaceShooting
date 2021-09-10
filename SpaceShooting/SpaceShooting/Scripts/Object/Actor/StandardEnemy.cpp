#include "StandardEnemy.h"

#include "../../Manager/BulletFactory.h"
#include "../../Manager/ObjectManager.h"

namespace shooting::object {
    void StandardEnemy::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::STANDARD_ENEMY.name );
        collisionRadius = status::StandardEnemy::COLLISION_RADIUS;
        maxHp = status::StandardEnemy::MAX_HP;
        hp = maxHp;
        speed = status::StandardEnemy::SPEED;
    }

    void StandardEnemy::Update() {
        Shoot();
        Move();
    }

    void StandardEnemy::Move() {
        position.X += sin( TimeManager::ToSeconds( GetNowCount() ) ) * speed * timeManager.lock()->DeltaTime;
        position.Y += -cos( TimeManager::ToSeconds( GetNowCount() ) ) * speed * timeManager.lock()->DeltaTime;
    }

    void StandardEnemy::Shoot() {
        shotCount += timeManager.lock()->DeltaTime;
        if ( shotCount >= status::StandardEnemy::SHOT_INTERVAL ) {
            shotCount = 0;

            float shootAngle = position.Angle( ObjectManager::Instance()->PlayerPosition(), true );
            object::BulletFactory::Instance()->Create( status::ObjectKind::EnemyBullet,
                                                       status::BulletType::StandardBullet,
                                                       position,
                                                       shootAngle,
                                                       status::StandardEnemy::BULLET_SPEED,
                                                       status::StandardEnemy::ATTACK_POWER );
        }
    }
}  // namespace shooting::object

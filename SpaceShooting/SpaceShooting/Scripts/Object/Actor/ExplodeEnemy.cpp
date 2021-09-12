#include "ExplodeEnemy.h"

#include "../../Manager/BulletFactory.h"
#include "../../Manager/ObjectManager.h"

namespace shooting::object {
    void ExplodeEnemy::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::EXPLODE_ENEMY.name );
        collisionRadius = status::ExplodeEnemy::COLLISION_RADIUS;
        maxHp = status::ExplodeEnemy::MAX_HP;
        hp = maxHp;
        speed = status::ExplodeEnemy::SPEED;
    }

    void ExplodeEnemy::Update() {
        toPlayerVector = position.VectorTo( ObjectManager::Instance()->PlayerPosition() );

        Move();

        if ( toPlayerVector.Length() <= status::ExplodeEnemy::IGNITION_DISTANCE ) {
            // 一定距離まで近づいたら爆発
            Explosion();
        }
    }

    auto ExplodeEnemy::Collide( const ObjectBase& hit ) -> bool {
        if ( ObjectBase::Collide( hit ) ) {
            // 死んだら爆発
            Explosion();
        }

        return !isActive;
    }

    void ExplodeEnemy::Move() {
        auto direction = toPlayerVector.Normalized();
        position += direction * speed * timeManager.lock()->DeltaTime;

        angle = position.Angle( direction, true );
    }

    void ExplodeEnemy::Explosion() {
        float baseAngle = static_cast<float>( PI * 2 ) / status::ExplodeEnemy::DIFFUSION_INDEX;
        for ( uint32_t i = 0; i < status::ExplodeEnemy::DIFFUSION_INDEX; i++ ) {
            float shootAngle = angle + baseAngle * i;
            BulletFactory::Instance()->Create( status::ObjectKind::EnemyBullet, status::BulletType::StandardBullet, position, shootAngle );
        }

        isActive = false;
    }
}  // namespace shooting::object

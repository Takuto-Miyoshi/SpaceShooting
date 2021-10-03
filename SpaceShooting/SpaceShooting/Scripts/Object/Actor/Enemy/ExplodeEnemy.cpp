#include "ExplodeEnemy.h"

#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"

namespace shooting::object {
    void ExplodeEnemy::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::EXPLODE_ENEMY.name );

        objectStatus = status::enemy::ExplodeEnemy::OBJECT;
        actorStatus = status::enemy::ExplodeEnemy::ACTOR;
    }

    void ExplodeEnemy::DeathProcess() {
        Explosion();
    }

    void ExplodeEnemy::Update() {
        toPlayerVector = position.To( ObjectManager::Instance()->PlayerPosition() );

        Move();

        if ( toPlayerVector.Length() <= status::enemy::ExplodeEnemy::IGNITION_DISTANCE ) {
            // 一定距離まで近づいたら爆発
            Explosion();
        }
    }

    void ExplodeEnemy::Move() {
        auto direction = toPlayerVector.Normalized();
        MoveTo( direction );

        angle = position.AngleTo( direction );
    }

    void ExplodeEnemy::Explosion() {
        float baseAngle = static_cast<float>( PI * 2 ) / status::enemy::ExplodeEnemy::DIFFUSION_INDEX;
        for ( uint32_t i = 0; i < status::enemy::ExplodeEnemy::DIFFUSION_INDEX; i++ ) {
            float shootAngle = angle + baseAngle * i;
            BulletFactory::Instance()->Create( status::ObjectKind::EnemyBullet,
                                               status::bullet::Type::StandardBullet,
                                               position,
                                               shootAngle,
                                               status::enemy::ExplodeEnemy::BULLET );
        }

        isActive = false;
    }
}  // namespace shooting::object

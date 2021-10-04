#include "ExplodeEnemy.h"

#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Utility/Functions.h"

namespace shooting::object {
    void ExplodeEnemy::Start() {
        Initialize( image::EXPLODE_ENEMY.name,
                    status::enemy::ExplodeEnemy::OBJECT,
                    status::enemy::ExplodeEnemy::ACTOR,
                    status::enemy::ExplodeEnemy::ENEMY.Exp,
                    status::enemy::ExplodeEnemy::BULLET );
    }

    void ExplodeEnemy::DeathProcess() {
        Explosion();
        EnemyBase::DeathProcess();
    }

    void ExplodeEnemy::Update() {
        EnemyBase::Update();

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
            float target = angle + baseAngle * i;
            ShootTo( target );
        }

        isActive = false;
    }
}  // namespace shooting::object

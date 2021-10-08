#include "ExplodeEnemy.h"

#include "../../../Definition/StatusLoaderKey.h"
#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Manager/StatusLoader.h"
#include "../../../Utility/Functions.h"

namespace shooting::object {
    void ExplodeEnemy::Start() {
        Initialize( status::loaderKey::object::enemy::EXPLODE );

        auto& data = status::StatusLoader::Instance()->Get_a( status::loaderKey::object::enemy::EXPLODE );
        diffusionIndex = static_cast<uint32_t>( data.ExtraParam1 );
        ignitionDistance = data.ExtraParam2;
    }

    void ExplodeEnemy::DeathProcess() {
        Explosion();
        EnemyBase::DeathProcess();
    }

    void ExplodeEnemy::Update() {
        EnemyBase::Update();

        toPlayerVector = position.To( ObjectManager::Instance()->PlayerPosition() );

        Move();

        if ( toPlayerVector.Length() <= ignitionDistance ) {
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
        float baseAngle = static_cast<float>( PI * 2 ) / diffusionIndex;
        for ( uint32_t i = 0; i < diffusionIndex; i++ ) {
            float target = angle + baseAngle * i;
            ShootTo( target );
        }

        isActive = false;
    }
}  // namespace shooting::object

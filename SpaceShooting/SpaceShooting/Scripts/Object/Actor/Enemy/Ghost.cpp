#include "Ghost.h"

#include "../../../Definition/StatusLoaderKey.h"
#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Manager/StatusLoader.h"

namespace shooting::object {
    void Ghost::Start() {
        Initialize( status::loaderKey::object::enemy::GHOST );

        auto& data { status::StatusLoader::Instance()->Get_a( status::loaderKey::object::enemy::GHOST ) };
        transTime = data.ExtraParam1;
        wayIndex = static_cast<uint32_t>( data.ExtraParam2 );
        angleOffset = static_cast<float>( data.ExtraParam3 );
    }

    void Ghost::Update() {
        EnemyBase::Update();

        Look();
        Move();
    }

    void Ghost::Shoot() {
        target = ObjectManager::Instance()->PlayerPosition();

        const auto baseAngle { angle - angleOffset };
        for ( auto i { 0u }; i < wayIndex; i++ ) {
            const auto shootAngle { baseAngle + ( angleOffset * i ) };
            auto bullet { ShootTo( position, shootAngle ) };
            auto trans { BulletFactory::Instance()->CreateTrans( bullet, { baseBuletData, transTime } ) };
            trans->Stack( { 120, 6.0, 0.0, 0.0f, status::bullet::Type::HomingBullet, baseBuletData.GrowAttackPower } );
        }
    }

    void Ghost::Move() {
        MoveTo( Vector2::FromAngle( angle ) );
    }

    void Ghost::Look() {
        const auto lookAt { position.AngleTo( target ) };
        angle = SLerp<float>( angle, lookAt, 0.01 );
    }
}  // namespace shooting::object

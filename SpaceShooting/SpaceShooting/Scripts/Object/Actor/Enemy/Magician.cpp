﻿#include "Magician.h"

#include "../../../Definition/StatusLoaderKey.h"
#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Manager/StatusLoader.h"

namespace shooting::object {
    void Magician::Start() {
        Initialize( status::loaderKey::object::enemy::MAGICIAN );

        auto& data { status::StatusLoader::Instance()->Get_a( status::loaderKey::object::enemy::MAGICIAN ) };
        shootDistance = data.ObjectData.CollisionRadius * 2;

        bulletIndex = static_cast<uint32_t>( data.ExtraParam1 );
        toPlayerDistance = data.ExtraParam2;
        transTime = data.ExtraParam3;
    }

    void Magician::Update() {
        EnemyBase::Update();
    }

    void Magician::Shoot() {
        const auto baseAngle { TWICE_PI<float> / bulletIndex };
        const auto shootAngle { baseAngle * progress };

        auto bullet { ShootTo( position + Vector2<>::FromAngle<double>( shootAngle ) * shootDistance, shootAngle ) };
        auto trans { BulletFactory::Instance()->CreateTrans( bullet, { baseBuletData } ) };
        trans->Stack( { 180.0, 8.0, 0.0, 0.0f, status::bullet::Type::StandardBullet, baseBuletData.GrowAttackPower, transTime } );

        progress++;

        if ( progress == bulletIndex ) {
            progress = 0;
            Warp();
        }
    }

    void Magician::Warp() {
        auto warpTo { ObjectManager::Instance()->PlayerPosition() };
        warpTo += Vector2<double>::RandomUnit() * toPlayerDistance;
        position = warpTo;
    }
}  // namespace shooting::object

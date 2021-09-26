#include "WeaponBase.h"

#include "../Manager/TimeManager.h"

namespace shooting::weapon {
    void WeaponBase::Initialize( const object::ObjectBase& user ) {
        position = &user.Position;
        angle = &user.Angle;
        kind = ConvertKind( user.Kind );
    }

    void WeaponBase::Update() {
        timer -= TimeManager::Instance()->DeltaTime;
        if ( timer <= 0 ) {
            shootable = true;
        }
    }

    void WeaponBase::Shoot() {
        if ( shootable == false ) { return; }
        ShootProcess();
        ShootedProcess();
    }

    void WeaponBase::ShootedProcess() {
        shootable = false;
        timer = weaponStatus.Interval;
    }

    auto WeaponBase::ConvertKind( const object::status::ObjectKind& source ) const -> object::status::ObjectKind {
        switch ( source ) {
            case object::status::ObjectKind::Enemy: return object::status::ObjectKind::EnemyBullet;
            case object::status::ObjectKind::Player: return object::status::ObjectKind::PlayerBullet;
            default: return source;
        }
    }
}  // namespace shooting::weapon

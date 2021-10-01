#include "MachineGun.h"

#include "../Manager/BulletFactory.h"
#include "../Utility/Functions.h"

namespace shooting::weapon {
    void MachineGun::Initialize( const object::ObjectBase& user ) {
        WeaponBase::Initialize( user );

        weaponStatus = object::status::weapon::MachineGun::WEAPON;
    }

    void MachineGun::ShootProcess() {
        auto shootAngle = *angle + RandomFloat( object::status::weapon::MachineGun::DEVIATION );

        object::BulletFactory::Instance()->Create(
            kind,
            object::status::bullet::Type::StandardBullet,
            *position,
            shootAngle,
            object::status::weapon::MachineGun::BULLET );
    }
}  // namespace shooting::weapon

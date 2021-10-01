#include "StandardRifle.h"

#include "../Manager/BulletFactory.h"

namespace shooting::weapon {
    void StandardRifle::Initialize( const object::ObjectBase& user ) {
        WeaponBase::Initialize( user );

        weaponStatus = object::status::weapon::StandardRifle::WEAPON;
    }

    void StandardRifle::ShootProcess() {
        object::BulletFactory::Instance()->Create(
            kind,
            object::status::bullet::Type::StandardBullet,
            *position,
            *angle,
            object::status::weapon::StandardRifle::BULLET );
    }
}  // namespace shooting::weapon

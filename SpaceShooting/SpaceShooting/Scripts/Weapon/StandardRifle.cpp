#include "StandardRifle.h"

#include "../Manager/BulletFactory.h"

namespace shooting::weapon {
    void StandardRifle::Initialize( const object::ObjectBase& user ) {
        WeaponBase::Initialize( user );
        interval = object::status::weapon::StandardRifle::INTERVAL;
    }

    void StandardRifle::ShootProcess() {
        object::BulletFactory::Instance()->Create( kind,
                                                   object::status::BulletType::StandardBullet,
                                                   *position,
                                                   *angle,
                                                   object::status::weapon::StandardRifle::SPEED,
                                                   object::status::weapon::StandardRifle::ATTACK_POWER );
    }
}  // namespace shooting::weapon

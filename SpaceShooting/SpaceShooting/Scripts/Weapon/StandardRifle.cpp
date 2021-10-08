#include "StandardRifle.h"

#include "../Definition/StatusLoaderKey.h"

using namespace shooting::object;

namespace shooting::weapon {
    void StandardRifle::Initialize( const object::ActorBase& user, const uint8_t& useRarity ) {
        WeaponBase::Initialize( user, useRarity );

        InitializeWeapon( status::loaderKey::object::weapon::STANDARD_RIFLE );
    }

    void StandardRifle::ShootProcess() {
        ShootForward();
    }
}  // namespace shooting::weapon

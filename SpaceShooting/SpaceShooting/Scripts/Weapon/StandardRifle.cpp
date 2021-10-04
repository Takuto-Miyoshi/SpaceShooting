#include "StandardRifle.h"

using namespace shooting::object;

namespace shooting::weapon {
    void StandardRifle::Initialize( const object::ActorBase& user, const uint8_t& rarity ) {
        WeaponBase::Initialize( user, rarity );
        auto data = status::weapon::StandardRifle::list.at( rare );
        InitializeWeapon( data.WEAPON, data.BULLET );
    }

    void StandardRifle::ShootProcess() {
        ShootForward();
    }
}  // namespace shooting::weapon

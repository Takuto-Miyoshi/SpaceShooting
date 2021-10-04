#include "MachineGun.h"

#include "../Utility/Functions.h"

using namespace shooting::object;

namespace shooting::weapon {
    void MachineGun::Initialize( const object::ActorBase& user, const uint8_t& rarity ) {
        WeaponBase::Initialize( user, rarity );
        auto data = status::weapon::MachineGun::list.at( rare );
        InitializeWeapon( data.WEAPON, data.BULLET );
    }

    void MachineGun::ShootProcess() {
        auto shootAngle = *angle + RandomReal<float>( status::weapon::MachineGun::list.at( rare ).DEVIATION );
        ShootTo( shootAngle );
    }
}  // namespace shooting::weapon

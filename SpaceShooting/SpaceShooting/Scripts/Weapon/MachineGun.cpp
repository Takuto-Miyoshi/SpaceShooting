#include "MachineGun.h"

#include "../Definition/StatusLoaderKey.h"
#include "../Manager/StatusLoader.h"
#include "../Utility/Functions.h"

using namespace shooting::object;

namespace shooting::weapon {
    void MachineGun::Initialize( const object::ActorBase& user, const uint8_t& useRarity ) {
        WeaponBase::Initialize( user, useRarity );

        InitializeWeapon( status::loaderKey::object::weapon::MACHINE_GUN );

        auto& data = status::StatusLoader::Instance()->Get_a( status::loaderKey::object::weapon::MACHINE_GUN );
        deviation = static_cast<float>( data.ExtraParam1 );
    }

    void MachineGun::ShootProcess() {
        auto shootAngle = *angle + RandomReal<float>( deviation );
        ShootTo( shootAngle );
    }
}  // namespace shooting::weapon

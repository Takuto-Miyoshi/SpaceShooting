// 向いている方向に弾を乱射する

#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H

#include "WeaponBase.h"

namespace shooting::weapon {
    class MachineGun : public WeaponBase {
       public:
        MachineGun() = default;

        ~MachineGun() override = default;

       public:
        void Initialize( const object::ObjectBase& user ) override;

        void ShootProcess() override;
    };
}  // namespace shooting::weapon

#endif  // !MACHINE_GUN_H

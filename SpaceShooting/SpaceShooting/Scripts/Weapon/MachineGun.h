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
        void Initialize( const object::ActorBase& user, const uint8_t& useRarity ) override;

        void ShootProcess() override;

       private:
        float deviation { 0.0f };  // 振れ幅
    };
}  // namespace shooting::weapon

#endif  // !MACHINE_GUN_H

// 向いている方向に弾を発射する

#ifndef STANDARD_RIFLE_H
#define STANDARD_RIFLE_H

#include "WeaponBase.h"

namespace shooting::weapon {
    class StandardRifle : public WeaponBase {
       public:
        StandardRifle() = default;

        ~StandardRifle() override = default;

       public:
        void Initialize( const object::ObjectBase& user ) override;

        void ShootProcess() override;
    };
}  // namespace shooting::weapon

#endif  // !STANDARD_RIFLE_H

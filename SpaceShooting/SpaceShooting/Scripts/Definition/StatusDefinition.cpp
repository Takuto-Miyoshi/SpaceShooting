#include "StatusDefinition.h"

namespace shooting::object {
    // --------- Object ----------

    const uint32_t ObjectSetting::OBJECT_CAPACITY { 500 };
    const double ObjectSetting::VALID_DISTANCE { 1000.0 };
    const double ObjectSetting::SPAWN_INTERVAL { 5.0 };
    const uint32_t ObjectSetting::MAX_LEVEL { 100 };

    // --------------------------
    // --------- Lottery ----------

    const uint32_t Lottery::BOX_CAPACITY { 10 };

    // --------------------------

    namespace status {
        auto Grow::Dest() -> double {
            auto value = Fixed + RandomReal( Fluctuation );
            return PercentOf( value, UseRatio );
        }

        void Actor::LevelUp() {
            auto increaseHp = GrowHp.Dest();
            MaxHp += increaseHp;
            Hp += increaseHp;
        }

        void Bullet::LevelUp() {
            AttackPower += GrowAttackPower.Dest();
        }

        const double BulletSetting::LIFE_SPAN_OF_BULLET { 5.0 };

        const double ExperienceSetting::RATE_OF_LEVEL_TO_EXP { 5.0 };
        const double ExperienceSetting::RATE_OF_NEXT_LEVEL { 39.1 };
        const int32_t ExperienceSetting::MULTIPLE_OF_NEXT_LEVEL { 3 };

        // --------------------------

        const Object Player::OBJECT {
            32.0  // CollisionRadius
        };
        const Actor Player::ACTOR {
            100.0,  // MaxHp
            100.0,  // Hp
            120.0,  // Speed
            { 5.0, 3.0, 85.0 }  // GrowHp
        };

        // --------------------------

        namespace bullet {
            const Object StandardBullet::OBJECT {
                8.0
            };

            const Object HomingBullet::OBJECT {
                8.0
            };
            const double HomingBullet::LERP_POWER { 1.6 };
        }  // namespace bullet

        // --------------------------

        namespace enemy {
            const Object StandardEnemy::OBJECT {
                16.0
            };
            const Actor StandardEnemy::ACTOR {
                30.0,
                30.0,
                140.0,
                { 4.0, 2.5, 95.0 }
            };
            const Bullet StandardEnemy::BULLET {
                200.0,  // BulletSpeed
                5.0,  // AttackPower
                0.0,  // Acceleration
                0.0,  // AngulerVelocity
                bullet::Type::StandardBullet,  // BulletType
                { 2.5, 1.5, 30.0 }  // GrowAttackPower
            };
            const Enemy StandardEnemy::ENEMY {
                100.0,  // SpawnRate
                30.0,  // ChainRate
                10,  // Exp
            };
            const double StandardEnemy::SHOT_INTERVAL { 3.0 };

            const Object ExplodeEnemy::OBJECT {
                16.0
            };
            const Actor ExplodeEnemy::ACTOR {
                20.0,
                20.0,
                100.0,
                { 3.5, 1.0, 100.0 }
            };
            const Bullet ExplodeEnemy::BULLET {
                300.0,
                7.0,
                0.0,
                0.0,
                bullet::Type::StandardBullet,
                { 1, 0.5, 80.0 }
            };
            const Enemy ExplodeEnemy::ENEMY {
                50.0,
                15.0,
                14,
            };
            const uint32_t ExplodeEnemy::DIFFUSION_INDEX { 8 };
            const double ExplodeEnemy::IGNITION_DISTANCE { 100.0 };
        }  // namespace enemy

        // --------------------------

        namespace weapon {
            const std::array<weaponList::StandardRifle, WeaponSetting::MAX_RARE> weapon::StandardRifle::list {
                { { 1.1, 210.0, 7.0, -20.0, 0.0f, bullet::Type::StandardBullet, {} },
                  { 1.0, 230.0, 8.0, 0.0, 0.0f, bullet::Type::StandardBullet, {} },
                  { 0.8, 240.0, 9.0, 3.0, 0.0f, bullet::Type::StandardBullet, {} },
                  { 0.7, 260.0, 10.0, 50.0, 0.0f, bullet::Type::StandardBullet, {} },
                  { 0.6, 280.0, 12.0, 80.0, 0.0f, bullet::Type::StandardBullet, {} } }
            };

            const std::array<weaponList::MachineGun, WeaponSetting::MAX_RARE> weapon::MachineGun::list {
                { { 0.35, 230, 2.0, -40.0, 0.0f, bullet::Type::StandardBullet, {}, 0.45f },
                  { 0.3, 250, 3.5, -30.0, 0.0f, bullet::Type::StandardBullet, {}, 0.4f },
                  { 0.25, 260, 4.5, -20.0, 0.0f, bullet::Type::StandardBullet, {}, 0.3f },
                  { 0.2, 280, 6.0, -10.0, 0.0f, bullet::Type::StandardBullet, {}, 0.23f },
                  { 0.15, 300, 7.0, 0.0, 0.0f, bullet::Type::StandardBullet, {}, 0.15f } }
            };
        }  // namespace weapon

        namespace weaponList {
        }  // namespace weaponList

        // --------------------------

    }  // namespace status
}  // namespace shooting::object

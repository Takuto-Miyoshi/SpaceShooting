#include "StatusDefinition.h"

namespace shooting::object {
    // --------- Object ----------

    const uint32_t ObjectSetting::OBJECT_CAPACITY { 500 };
    const double ObjectSetting::VALID_DISTANCE { 1000.0 };
    const double ObjectSetting::SPAWN_INTERVAL { 5.0 };

    // --------------------------
    // --------- Lottery ----------

    const uint32_t Lottery::BOX_CAPACITY { 10 };

    namespace status {
        const double BulletSetting::LIFE_SPAN_OF_BULLET { 5.0 };

        // --------------------------

        const Object Player::OBJECT {
            32.0  // CollisionRadius
        };
        const Actor Player::ACTOR {
            100.0,  // MaxHp
            100.0,  // Hp
            120.0  // Speed
        };

        // --------------------------

        namespace bullet {
            const Object StandardBullet::OBJECT {
                8.0
            };

            const Object HomingBullet::OBJECT {
                8.0
            };
        }  // namespace bullet

        // --------------------------

        namespace enemy {
            const Object StandardEnemy::OBJECT {
                16.0
            };
            const Actor StandardEnemy::ACTOR {
                30.0,
                30.0,
                140.0
            };
            const Bullet StandardEnemy::BULLET {
                200.0,  // BulletSpeed
                5.0,  // AttackPower
                0.0,  // Acceleration
                0.0  // AngulerVelocity
            };
            const Spawn StandardEnemy::SPAWN {
                100.0,  // SpawnRate
                30.0  // ChainRate
            };
            const double StandardEnemy::SHOT_INTERVAL { 3.0 };

            const Object ExplodeEnemy::OBJECT {
                16.0
            };
            const Actor ExplodeEnemy::ACTOR {
                20.0,
                20.0,
                100.0
            };
            const Bullet ExplodeEnemy::BULLET {
                300.0,
                7.0,
                0.0,
                0.0
            };
            const Spawn ExplodeEnemy::SPAWN {
                50.0,
                15.0
            };
            const uint32_t ExplodeEnemy::DIFFUSION_INDEX { 8 };
            const double ExplodeEnemy::IGNITION_DISTANCE { 100.0 };
        }  // namespace enemy

        // --------------------------

        namespace weapon {
            const Weapon StandardRifle::WEAPON {
                1.0  // Interval
            };
            const Bullet StandardRifle::BULLET {
                240.0,
                8.0,
                0.0,
                0.0
            };
        }  // namespace weapon

        // --------------------------

    }  // namespace status
}  // namespace shooting::object

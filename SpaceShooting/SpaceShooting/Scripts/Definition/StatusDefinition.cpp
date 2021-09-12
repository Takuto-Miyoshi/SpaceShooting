#include "StatusDefinition.h"

namespace shooting::object {
    // --------- Object ----------
    const uint32_t Object::OBJECT_CAPACITY { 500 };
    const double Object::VALID_DISTANCE { 1000.0 };
    const double Object::SPAWN_INTERVAL { 5.0 };

    // --------- Lottery ----------
    const uint32_t Lottery::BOX_CAPACITY { 10 };

    namespace status {
        // --------- Player ----------
        const double Player::SPEED { 120.0 };
        const double Player::COLLISION_RADIUS { 32.0 };
        const double Player::MAX_HP { 100.0 };

        // --------- Enemy ----------
        const double StandardEnemy::COLLISION_RADIUS { 16.0 };
        const double StandardEnemy::MAX_HP { 30.0 };
        const double StandardEnemy::SPEED { 140.0 };
        const double StandardEnemy::SPAWN_RATE { 100.0 };
        const double StandardEnemy::CHAIN_RATE { 30.0 };
        const double StandardEnemy::SHOT_INTERVAL { 3.0 };

        const double ExplodeEnemy::COLLISION_RADIUS { 16.0 };
        const double ExplodeEnemy::MAX_HP { 20.0 };
        const double ExplodeEnemy::SPEED { 100.0 };
        const double ExplodeEnemy::SPAWN_RATE { 50.0 };
        const double ExplodeEnemy::CHAIN_RATE { 15.0 };
        const uint32_t ExplodeEnemy::DIFFUSION_INDEX { 8 };
        const double ExplodeEnemy::IGNITION_DISTANCE { 100.0 };

        // --------- Bullet ----------
        const double Bullet::LIFE_SPAN_OF_BULLET { 5.0 };

        const double StandardBullet::SPEED { 200.0 };
        const double StandardBullet::COLLISION_RADIUS { 8.0 };
        const double StandardBullet::ATTACK_POWER { 5.0 };
    }  // namespace status
}  // namespace shooting::object

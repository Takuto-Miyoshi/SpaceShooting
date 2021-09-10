// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

#include <cstdint>

namespace shooting::object {
    struct Object {
        static const uint32_t OBJECT_CAPACITY;
        static const double VALID_DISTANCE;
        static const double SPAWN_INTERVAL;
    };

    struct Lottery {
        static const uint32_t BOX_CAPACITY;
    };

    namespace status {
        enum class ObjectKind {
            Player,
            PlayerBullet,
            Enemy,
            EnemyBullet
        };

        enum class BulletType {
            StandardBullet,
        };

        struct Player {
            static const double COLLISION_RADIUS;
            static const double MAX_HP;
            static const double SPEED;
        };

        struct StandardEnemy {
            static const double COLLISION_RADIUS;
            static const double MAX_HP;
            static const double SPEED;

            static const double BULLET_SPEED;
            static const double ATTACK_POWER;

            static const double SPAWN_RATE;
            static const double CHAIN_RATE;

            static const double SHOT_INTERVAL;
        };

        struct ExplodeEnemy {
            static const double COLLISION_RADIUS;
            static const double MAX_HP;
            static const double SPEED;

            static const double BULLET_SPEED;
            static const double ATTACK_POWER;

            static const double SPAWN_RATE;
            static const double CHAIN_RATE;

            static const uint32_t DIFFUSION_INDEX;
            static const double IGNITION_DISTANCE;
        };

        struct Bullet {
            static const double LIFE_SPAN_OF_BULLET;
        };

        struct StandardBullet {
            static const double COLLISION_RADIUS;
        };

        namespace weapon {
            struct StandardRifle {
                static const double SPEED;
                static const double ATTACK_POWER;
                static const double INTERVAL;
            };
        }  // namespace weapon
    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

// StatusLoaderで使用する定数群

#ifndef STATUS_LOADER_KEY_H
#define STATUS_LOADER_KEY_H

#include <any>
#include <map>
#include <string>

namespace shooting::object::status::loaderKey {
    namespace path {
        static const std::string STATUS { "Database/Status.csv" };
        static const std::string SPAWN { "Database/Spawn.csv" };
    }  // namespace path

    namespace read {
        static const std::string STATUS { "STATUS" };
        static const std::string SPAWN { "SPAWN" };
    }  // namespace read

    namespace command {
        static const std::string COMMAND { "command" };
        static const std::string CONSTANT { "constant" };
        static const std::string SKIP { "skip" };
        static const std::string START { "start" };
        static const std::string END { "end" };
        static constexpr char BREAK { ',' };
        static const std::string NONE { "None" };
    }  // namespace command

    namespace category {
        static const std::string PLAYER { "Player" };
        static const std::string ENEMY { "Enemy" };
        static const std::string BULLET { "Bullet" };
        static const std::string WEAPON { "Weapon" };
    }  // namespace category

    namespace parameter {
        static const std::string Category { "CATEGORY" };
        static const std::string Name { "NAME" };
        static const std::string Id { "ID" };

        namespace object {
            static const std::string CollisionRadius { "OBJECT_COLLISION_RADIUS" };
            static const std::string GraphicPath { "GRAPHIC_PATH" };
        }  // namespace object

        namespace actor {
            static const std::string MaxHp { "ACTOR_MAX_HP" };
            static const std::string Hp { "ACTOR_HP" };
            static const std::string Speed { "ACTOR_SPEED" };

            namespace grow {
                static const std::string Fixed { "ACTOR_GROWHP_FIXED" };
                static const std::string Fluctuation { "ACTOR_GROWHP_FLUCTUATION" };
                static const std::string UseRatio { "ACTOR_GROWHP_USE_RATIO" };
            }  // namespace grow
        }  // namespace actor

        namespace bullet {
            static const std::string Speed { "BULLET_SPEED" };
            static const std::string AttackPower { "BULLET_ATTACK_POWER" };
            static const std::string Acceleration { "BULLET_ACCELERATION" };
            static const std::string AngulerVelocity { "BULLET_ANGULER_VELOCITY" };
            static const std::string Type { "BULLET_TYPE" };

            namespace grow {
                static const std::string Fixed { "BULLET_GROWATTACKPOWER_FIXED" };
                static const std::string Fluctuation { "BULLET_GROWATTACKPOWER_FLUCTUATION" };
                static const std::string UseRatio { "BULLET_GROWATTACKPOWER_USE_RATIO" };
            }  // namespace grow
        }  // namespace bullet

        namespace enemy {
            static const std::string Exp { "ENEMY_EXP" };
            static const std::string Interval { "ENEMY_INTERVAL" };
        }  // namespace enemy

        namespace weapon {
            static const std::string Interval { "WEAPON_INTERVAL" };
            static const std::string Rarity { "WEAPON_RARITY" };
        }  // namespace weapon

        namespace extra {
            static const std::string Param1 { "EXTRA_PARAM1" };
            static const std::string Param2 { "EXTRA_PARAM2" };
            static const std::string Param3 { "EXTRA_PARAM3" };
        }  // namespace extra

        static std::map<std::string, uint32_t> List {
            { Category, 0 },
            { Name, 0 },
            { Id, 0 },
            { object::CollisionRadius, 0 },
            { object::GraphicPath, 0 },
            { actor::MaxHp, 0 },
            { actor::Hp, 0 },
            { actor::Speed, 0 },
            { actor::grow::Fixed, 0 },
            { actor::grow::Fluctuation, 0 },
            { actor::grow::UseRatio, 0 },
            { bullet::Speed, 0 },
            { bullet::AttackPower, 0 },
            { bullet::Acceleration, 0 },
            { bullet::AngulerVelocity, 0 },
            { bullet::Type, 0 },
            { bullet::grow::Fixed, 0 },
            { bullet::grow::Fluctuation, 0 },
            { bullet::grow::UseRatio, 0 },
            { enemy::Exp, 0 },
            { enemy::Interval, 0 },
            { weapon::Interval, 0 },
            { weapon::Rarity, 0 },
            { extra::Param1, 0 },
            { extra::Param2, 0 },
            { extra::Param3, 0 },
        };

        static auto IdOn( const std::string& str ) -> uint32_t& {
            return List.at( str );
        }
    }  // namespace parameter

    namespace object {
        static const std::string PLAYER { "Player" };

        namespace enemy {
            static const std::string STANDARD { "StandardEnemy" };
            static const std::string EXPLODE { "ExplodeEnemy" };
        }  // namespace enemy

        namespace bullet {
            static const std::string STANDARD { "StandardBullet" };
            static const std::string HOMING { "HomingBullet" };
        }  // namespace bullet

        namespace weapon {
            static const std::string STANDARD_RIFLE { "StandardRifle" };
            static const std::string MACHINE_GUN { "MachineGun" };
        }  // namespace weapon
    }  // namespace object

    namespace spawn {
        static const std::string GROUP { "GROUP" };
        static const std::string SPAWN_TYPE { "SPAWN_TYPE" };
        static const std::string SPAWN_RATE { "SPAWN_RATE" };
        static const std::string CHAIN_RATE { "CHAIN_RATE" };
        static const std::string MIN_LEVEL { "MIN_LEVEL" };
        static const std::string MAX_LEVEL { "MAX_LEVEL" };
        static const std::string NEXT_INTERVAL { "NEXT_INTERVAL" };

        static std::map<std::string, uint32_t> List {
            { GROUP, 0 },
            { SPAWN_TYPE, 0 },
            { SPAWN_RATE, 0 },
            { CHAIN_RATE, 0 },
            { MIN_LEVEL, 0 },
            { MAX_LEVEL, 0 },
            { NEXT_INTERVAL, 0 },
        };

        static auto IdOn( const std::string& str ) -> uint32_t& {
            return List.at( str );
        }
    }  // namespace spawn
}  // namespace shooting::object::status::loaderKey

#endif  // !STATUS_LOADER_KEY_H

// StatusLoaderで使用する定数群

#ifndef STATUS_LOADER_KEY_H
#define STATUS_LOADER_KEY_H

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
        static const std::string CATEGORY { "CATEGORY" };
        static const std::string NAME { "NAME" };
        static const std::string ID { "ID" };

        namespace object {
            static const std::string COLLISION_RADIUS { "OBJECT_COLLISION_RADIUS" };
            static const std::string GRAPHIC_PATH { "GRAPHIC_PATH" };
        }  // namespace object

        namespace actor {
            static const std::string MAX_HP { "ACTOR_MAX_HP" };
            static const std::string HP { "ACTOR_HP" };
            static const std::string SPEED { "ACTOR_SPEED" };

            namespace grow {
                static const std::string FIXED { "ACTOR_GROWHP_FIXED" };
                static const std::string FLUCTUATION { "ACTOR_GROWHP_FLUCTUATION" };
                static const std::string USE_RATIO { "ACTOR_GROWHP_USE_RATIO" };
            }  // namespace grow
        }  // namespace actor

        namespace bullet {
            static const std::string SPEED { "BULLET_SPEED" };
            static const std::string ATTACK_POWER { "BULLET_ATTACK_POWER" };
            static const std::string ACCELERATION { "BULLET_ACCELERATION" };
            static const std::string ANGULER_VELOCITY { "BULLET_ANGULER_VELOCITY" };
            static const std::string TYPE { "BULLET_TYPE" };

            namespace grow {
                static const std::string FIXED { "BULLET_GROWATTACKPOWER_FIXED" };
                static const std::string FLUCTUATION { "BULLET_GROWATTACKPOWER_FLUCTUATION" };
                static const std::string USE_RATIO { "BULLET_GROWATTACKPOWER_USE_RATIO" };
            }  // namespace grow
        }  // namespace bullet

        namespace enemy {
            static const std::string EXP { "ENEMY_EXP" };
            static const std::string INTERVAL { "ENEMY_INTERVAL" };
        }  // namespace enemy

        namespace weapon {
            static const std::string INTERVAL { "WEAPON_INTERVAL" };
            static const std::string RARITY { "WEAPON_RARITY" };
        }  // namespace weapon

        namespace extra {
            static const std::string PARAM1 { "EXTRA_PARAM1" };
            static const std::string PARAM2 { "EXTRA_PARAM2" };
            static const std::string PARAM3 { "EXTRA_PARAM3" };
        }  // namespace extra

        static std::map<std::string, uint32_t> List {
            { CATEGORY, 0 },
            { NAME, 0 },
            { ID, 0 },
            { object::COLLISION_RADIUS, 0 },
            { object::GRAPHIC_PATH, 0 },
            { actor::MAX_HP, 0 },
            { actor::HP, 0 },
            { actor::SPEED, 0 },
            { actor::grow::FIXED, 0 },
            { actor::grow::FLUCTUATION, 0 },
            { actor::grow::USE_RATIO, 0 },
            { bullet::SPEED, 0 },
            { bullet::ATTACK_POWER, 0 },
            { bullet::ACCELERATION, 0 },
            { bullet::ANGULER_VELOCITY, 0 },
            { bullet::TYPE, 0 },
            { bullet::grow::FIXED, 0 },
            { bullet::grow::FLUCTUATION, 0 },
            { bullet::grow::USE_RATIO, 0 },
            { enemy::EXP, 0 },
            { enemy::INTERVAL, 0 },
            { weapon::INTERVAL, 0 },
            { weapon::RARITY, 0 },
            { extra::PARAM1, 0 },
            { extra::PARAM2, 0 },
            { extra::PARAM3, 0 },
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

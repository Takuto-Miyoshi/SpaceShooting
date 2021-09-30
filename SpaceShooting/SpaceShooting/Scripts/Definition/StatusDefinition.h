// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

#include <cstdint>

namespace shooting::object {
    struct ObjectSetting {
        static const uint32_t OBJECT_CAPACITY;  // objectListのcapacity初期値
        static const double VALID_DISTANCE;  // X:0,Y:0からオブジェクトの有効距離
        static const double SPAWN_INTERVAL;  // 敵の出現する間隔
    };

    struct Lottery {
        static const uint32_t BOX_CAPACITY;  // lotteryBoxのcapacity初期値
    };

    // ----------------------------

    namespace status {
        /// @brief オブジェクトの区分
        enum class ObjectKind {
            Player,  // プレイヤー
            PlayerBullet,  // プレイヤーの放った弾
            Enemy,  // 敵
            EnemyBullet  // 敵の放った弾
        };

        // ----------------------------
        // ---------- Status ----------

        // オブジェクトのデータ
        struct Object {
            double CollisionRadius { 0.0 };  // 当たり判定の半径
        };

        // アクターのデータ
        struct Actor {
            double MaxHp { 0.0 };  // 最大HP
            double Hp { 0.0 };  // 現在HP
            double Speed { 0.0 };  // 移動速度
        };

        // 敵出現データ
        struct Spawn {
            double SpawnRate { 0.0 };  // 出現する確率
            double ChainRate { 0.0 };  // 連鎖して出現する確率
        };

        // 弾データ
        struct Bullet {
            double Speed { 0.0 };  // 発射する弾の速度
            double AttackPower { 0.0 };  // 発射する弾の威力
            double Acceleration { 0.0 };  // 加速度
            float AngulerVelocity { 0.0f };  // 角速度
        };

        // 武器データ
        struct Weapon {
            double Interval { 1.0 };  // 弾の発射間隔
        };

        // 弾設定
        struct BulletSetting {
            static const double LIFE_SPAN_OF_BULLET;  // 弾の生存可能時間
        };

        // ----------------------------

        struct Player {
            static const Object OBJECT;
            static const Actor ACTOR;
        };

        // ----------------------------

        namespace enemy {
            /// @brief 敵の種類
            enum class Type {
                StandardEnemy,
                ExplodeEnemy,
            };

            struct StandardEnemy {
                static const Object OBJECT;
                static const Actor ACTOR;
                static const Bullet BULLET;
                static const Spawn SPAWN;

                static const double SHOT_INTERVAL;  // 射撃間隔
            };

            struct ExplodeEnemy {
                static const Object OBJECT;
                static const Actor ACTOR;
                static const Bullet BULLET;
                static const Spawn SPAWN;

                static const uint32_t DIFFUSION_INDEX;
                static const double IGNITION_DISTANCE;
            };
        }  // namespace enemy

        // ----------------------------

        namespace bullet {
            /// @brief 弾の種類
            enum class Type {
                StandardBullet,
                HomingBullet,
            };

            struct StandardBullet {
                static const Object OBJECT;
            };

            struct HomingBullet {
                static const Object OBJECT;
            };
        }  // namespace bullet

        // ----------------------------

        namespace weapon {
            struct StandardRifle {
                static const Weapon WEAPON;
                static const Bullet BULLET;
            };
        }  // namespace weapon

        // ----------------------------

    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

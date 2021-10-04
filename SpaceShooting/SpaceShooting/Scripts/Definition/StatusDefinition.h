// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

#include <array>
#include <cstdint>
#include <functional>

#include "../Utility/Functions.h"

namespace shooting::object {
    struct ObjectSetting {
        static const uint32_t OBJECT_CAPACITY;  // objectListのcapacity初期値
        static const double VALID_DISTANCE;  // X:0,Y:0からオブジェクトの有効距離
        static const double SPAWN_INTERVAL;  // 敵の出現する間隔
        static const uint32_t MAX_LEVEL;  // 最大レベル
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

        namespace bullet {
            /// @brief 弾の種類
            enum class Type {
                StandardBullet,
                HomingBullet,
            };
        }  // namespace bullet

        // ----------------------------
        // ---------- Status ----------

        // オブジェクトのデータ
        struct Object {
            double CollisionRadius { 0.0 };  // 当たり判定の半径
        };

        // 成長データ
        struct Grow {
            /// @brief 上昇値を算出
            auto Dest() -> double;

            double Fixed { 0.0 };  // 固定値
            double Fluctuation { 0.0 };  // 変動幅
            double UseRatio { 100.0 };  // FixedとFluctuationから出た値の何％使用するか
        };

        // アクターのデータ
        struct Actor {
            /// @brief HPを最大まで回復
            constexpr void HealMax() {
                Hp = MaxHp;
            }

            /// @brief GrowXXをもとにステータスを上昇させる
            void LevelUp();

            double MaxHp { 0.0 };  // 最大HP
            double Hp { 0.0 };  // 現在HP
            double Speed { 0.0 };  // 移動速度

            Grow GrowHp {};  // HPの成長データ
        };

        // 経験値
        struct Experience {
            uint32_t Point { 0 };  // 現在経験値
            uint32_t Next { 0 };  // 次のレベルに必要な経験値
        };

        // 経験値設定
        struct ExperienceSetting {
            static const double RATE_OF_LEVEL_TO_EXP;  // 敵の取得経験値に対するレベルの影響率

            static const double RATE_OF_NEXT_LEVEL;  // 次のレベルに必要な経験値の計算 @n .. + next * (RATE_OF_NEXT_LEVEL / 100.0)
            static const int32_t MULTIPLE_OF_NEXT_LEVEL;  // 次のレベルに必要な経験値の計算 @n ..) * MULTIPLE_OF_NEXT_LEVEL + ..
        };

        // 武器設定
        struct WeaponSetting {
            static constexpr uint8_t MAX_RARE { 5 };  // 武器の最大レア度

            // レア度
            struct Rare {
                static constexpr uint8_t BROKEN { 0 };  // こわれた : 0
                static constexpr uint8_t NORMAL { 1 };  // ふつう : 1
                static constexpr uint8_t GREAT { 2 };  // すぐれた : 2
                static constexpr uint8_t MASTER { 3 };  // たつじん : 3
                static constexpr uint8_t LEGENDERY { 4 };  // でんせつ : 4
            };
        };

        // 敵データ
        struct Enemy {
            double SpawnRate { 0.0 };  // 出現する確率
            double ChainRate { 0.0 };  // 連鎖して出現する確率

            uint32_t Exp { 0 };  // 得られる経験値
        };

        // 弾データ
        struct Bullet {
            /// @brief GrowXXをもとにステータスを上昇させる
            void LevelUp();

            double Speed { 0.0 };  // 発射する弾の速度
            double AttackPower { 0.0 };  // 発射する弾の威力
            double Acceleration { 0.0 };  // 加速度
            float AngularVelocity { 0.0f };  // 角速度
            bullet::Type BulletType {};  // 弾の種類

            Grow GrowAttackPower {};  // AttackPowerの成長データ
        };

        // 弾設定
        struct BulletSetting {
            static const double LIFE_SPAN_OF_BULLET;  // 弾の生存可能時間
        };

        // 武器データ
        struct Weapon {
            double Interval { 1.0 };  // 弾の発射間隔
        };

        // ----------------------------

        struct Player {
            static const Object OBJECT;
            static const Actor ACTOR;
        };

        // ----------------------------

        namespace bullet {
            // 変化弾データ
            struct TransData {
                bullet::Type TransTo;  // 変化先
                Bullet ToBulletData;  // 変化先の弾データ
                double TimeToTrans;  // 変化するまでの時間
            };

            struct StandardBullet {
                static const Object OBJECT;
            };

            struct HomingBullet {
                static const Object OBJECT;
                static const double LERP_POWER;  // 角度変化のための線形補完の強さ @n ×deltaTimeされる
            };
        }  // namespace bullet

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
                static const Enemy ENEMY;

                static const double SHOT_INTERVAL;  // 射撃間隔
            };

            struct ExplodeEnemy {
                static const Object OBJECT;
                static const Actor ACTOR;
                static const Bullet BULLET;
                static const Enemy ENEMY;

                static const uint32_t DIFFUSION_INDEX;
                static const double IGNITION_DISTANCE;
            };
        }  // namespace enemy

        // ----------------------------

        // 武器の種類
        namespace weaponList {
            struct StandardRifle {
                Weapon WEAPON;
                Bullet BULLET;
            };

            struct MachineGun {
                Weapon WEAPON;
                Bullet BULLET;

                float DEVIATION;
            };
        }  // namespace weaponList

        // レア度設定された武器
        namespace weapon {
            struct StandardRifle {
                static const std::array<weaponList::StandardRifle, WeaponSetting::MAX_RARE> list;
            };

            struct MachineGun {
                static const std::array<weaponList::MachineGun, WeaponSetting::MAX_RARE> list;
            };
        }  // namespace weapon

        // ----------------------------

    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

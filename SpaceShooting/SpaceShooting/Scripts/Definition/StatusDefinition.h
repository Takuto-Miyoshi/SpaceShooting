// 各基礎ステータスを定義

#ifndef STATUS_DEFINITION_H
#define STATUS_DEFINITION_H

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

        namespace enemy {
            /// @brief 敵の種類
            enum class Type {
                None,
                StandardEnemy,
                ExplodeEnemy,
                NeedleEnemy,
            };
        }  // namespace enemy

        namespace bullet {
            /// @brief 弾の種類
            enum class Type {
                None,
                StandardBullet,
                HomingBullet,
            };
        }  // namespace bullet

        // ----------------------------
        // ---------- Status ----------

        // オブジェクトのデータ
        struct Object {
            double CollisionRadius { 0.0 };  // 当たり判定の半径
            int32_t GraphicHandle { 0 };  // 画像ハンドル
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
                static constexpr uint8_t BROKEN { 1 };  // こわれた : 1
                static constexpr uint8_t NORMAL { 2 };  // ふつう : 2
                static constexpr uint8_t GREAT { 3 };  // すぐれた : 3
                static constexpr uint8_t MASTER { 4 };  // たつじん : 4
                static constexpr uint8_t LEGENDARY { 5 };  // でんせつ : 5
            };
        };

        // 敵データ
        struct Enemy {
            uint32_t Exp { 0 };  // 得られる経験値
            double Interval { 0.0 };  // 攻撃間隔
        };

        // 敵出現データ
        struct SpawnData {
            uint32_t Group { 0 };  // 所属グループ
            enemy::Type SpawnType {};  // 出現する敵
            double SpawnRate { 0.0 };  // 出現リストに登録される確率
            double ChainRate { 0.0 };  // 連鎖して出現する確率

            uint32_t MinLevel { 0 };  // 最小レベル
            uint32_t MaxLevel { 0 };  // 最大レベル
            double NextInterval { 0.0 };  // 次の敵が出現するまでの時間
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
            uint32_t Rarity { 0 };  // 武器のレア度
        };

        // ----------------------------

        namespace bullet {
            // 変化弾データ
            struct TransData {
                bullet::Type TransTo {};  // 変化先
                Bullet ToBulletData {};  // 変化先の弾データ
                double TimeToTrans { 0.0 };  // 変化するまでの時間
            };
        }  // namespace bullet

        // ----------------------------

    }  // namespace status
}  // namespace shooting::object

#endif  // !STATUS_DEFINITION_H

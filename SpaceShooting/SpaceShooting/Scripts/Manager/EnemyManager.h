﻿// 敵の自動生成と管理

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <cstdint>
#include <vector>

#include "../Definition/StatusDefinition.h"
#include "../Manager/StatusLoader.h"
#include "../Object/Actor/Enemy/EnemyBase.h"
#include "../Utility/Property.hpp"
#include "../Utility/Timer.h"
#include "../Utility/Vector.hpp"
#include "ObjectManager.h"

namespace shooting::object {
    class EnemyManager {
       public:
        EnemyManager() = default;

        ~EnemyManager() = default;

       public:
        /// @brief 初期化
        void Initialize();

        /// @brief 抽選リストを全てリセット
        void Reset() noexcept;

       private:
        void Spawn();

        /// @brief 抽選リストの中から敵データをランダムに取得
        auto Lottery() -> const status::SpawnData&;

        /// @brief 敵を生成
        /// @param type 敵のタイプ
        /// @param chainChance 連鎖して生成する確率
        void Generate( status::SpawnData spawnData );

        /// @brief タイプをもとに敵を生成する
        void GenerateByType( const status::SpawnData& spawnData );

        /// @brief 敵を作成
        /// @tparam T EnemyBaseを継承のみ許容
        template<typename T>
        auto GenerateEnemy() -> typename std::enable_if<std::derived_from<T, EnemyBase>, EnemyBase>::type* {
            return dynamic_cast<EnemyBase*>( ObjectManager::Instance()->CreateObject<T>( status::ObjectKind::Enemy, RandomPosition() ) );
        }

        /// @brief 百分率の確率にヒットしたかを取得
        auto HitOfTheTime( const double& chance ) -> bool;

        /// @brief 有効距離内でランダムな位置を取得
        auto RandomPosition() -> Vector2<double>;

        /// @brief レベルの設定
        void LevelSetting( EnemyBase& enemy, const status::SpawnData& spawnData );

       public:
        BasicProperty<uint32_t> UseGroup {
            useGroup, nullptr, [this]( uint32_t value ) {
                useGroup = value;
                lotteryBox = status::StatusLoader::Instance()->GetGroup( useGroup );
            }
        };

       private:
        static constexpr double DECREASE_RATE { 0.9 };  // chainChanceの減少率

        std::vector<status::SpawnData> lotteryBox {};  // 抽選登録用リスト
        std::vector<status::SpawnData> box {};  // 本抽選用リスト

        uint32_t useGroup { 0 };  // 使用する敵グループのID

        double interval { 0.0 };
        Timer timer { interval, [this]() { Spawn(); } };
    };
}  // namespace shooting::object

#endif  // !ENEMY_MANAGER_H

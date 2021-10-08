// 敵の自動生成と管理

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <cstdint>
#include <vector>

#include "../Definition/StatusDefinition.h"
#include "../Manager/StatusLoader.h"
#include "../Object/Actor/Enemy/EnemyBase.h"
#include "../Utility/Property.h"
#include "../Utility/Vector.h"
#include "ObjectManager.h"

namespace shooting::object {
    class EnemyManager {
       public:
        EnemyManager() = default;

        ~EnemyManager() = default;

       public:
        /// @brief 初期化
        void Initialize();

        /// @brief 更新
        void Update();

        /// @brief 抽選リストを全てリセット
        void Reset();

       private:
        /// @brief 抽選リストの中から敵データをランダムに取得
        auto Lottery() -> status::SpawnData;

        /// @brief 敵を生成
        /// @param type 敵のタイプ
        /// @param chainChance 連鎖して生成する確率
        void Generate( status::SpawnData spawnData );

        /// @brief タイプをもとに敵を生成する
        void GenerateByType( const status::SpawnData& spawnData );

        template<class T>
        auto GenerateEnemy() -> EnemyBase* {
            return dynamic_cast<EnemyBase*>( ObjectManager::Instance()->CreateObject<T>( status::ObjectKind::Enemy, RandomPosition() ) );
        }

        /// @brief 百分率の確率にヒットしたかを取得
        auto HitOfTheTime( const double& chance ) -> bool;

        /// @brief 有効距離内でランダムな位置を取得
        auto RandomPosition() -> Vector2;

        /// @brief レベルの設定
        void LevelSetting( EnemyBase& enemy, const status::SpawnData& spawnData );

       public:
        Property<uint32_t> UseGroup {
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

        double spawnTimer { 0.0 };
        double interval { 0.0 };
    };
}  // namespace shooting::object

#endif  // !ENEMY_MANAGER_H

// 敵の自動生成と管理

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <cstdint>
#include <vector>

#include "../Utility/Property.h"
#include "../Utility/Vector.h"

namespace shooting::object {
    class EnemyManager {
       public:
        enum class EnemyType {
            StandardEnemy,
            ExplodeEnemy,
        };

       private:
        struct LotteryData {
            EnemyType type;
            double spawnChance;
            double chainChance;
        };

       public:
        EnemyManager() = default;

        ~EnemyManager() = default;

       public:
        void Initialize();

        void Update();

        /// @brief 抽選リストに登録
        /// @param type 登録する敵
        /// @param spawnChance 本抽選に登録される確率
        /// @param chainChance 連鎖して召喚される確率
        void Register( EnemyType&& type, const double& spawnChance, const double& chainChance );

        /// @brief 抽選リストから登録解除
        void Unregister( const EnemyType& type );

        /// @brief 抽選リストを全てリセット
        void Reset();

       private:
        auto Lottery() -> LotteryData;

        void Generate( const EnemyType& type, double chainChance );

        void GenerateByType( const EnemyType& type );

        auto HitOfTheTime( const double& chance ) -> bool;

        auto RandomPosition() -> Vector2;

       private:
        static constexpr double DECREASE_RATE { 0.9 };

        std::vector<LotteryData> lotteryBox;
        std::vector<LotteryData> box;

        double spawnTimer { 0.0 };
    };
}  // namespace shooting::object

#endif  // !ENEMY_MANAGER_H

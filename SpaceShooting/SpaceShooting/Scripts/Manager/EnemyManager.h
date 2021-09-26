// 敵の自動生成と管理

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <cstdint>
#include <vector>

#include "../Definition/StatusDefinition.h"
#include "../Utility/Property.h"
#include "../Utility/Vector.h"

namespace shooting::object {
    class EnemyManager {
       private:
        struct LotteryData {
            status::enemy::Type type;
            double spawnChance;
            double chainChance;
        };

       public:
        EnemyManager() = default;

        ~EnemyManager() = default;

       public:
        /// @brief 初期化
        void Initialize();

        /// @brief 更新
        void Update();

        /// @brief 抽選リストに登録
        /// @param type 登録する敵
        /// @param spawnChance 本抽選に登録される確率
        /// @param chainChance 連鎖して召喚される確率
        void Register( status::enemy::Type&& type, const double& spawnChance, const double& chainChance );

        /// @brief 抽選リストから登録解除
        void Unregister( const status::enemy::Type& type );

        /// @brief 抽選リストを全てリセット
        void Reset();

       private:
        /// @brief 抽選リストの中から敵データをランダムに取得
        auto Lottery() -> LotteryData;

        /// @brief 敵を生成
        /// @param type 敵のタイプ
        /// @param chainChance 連鎖して生成する確率
        void Generate( const status::enemy::Type& type, double chainChance );

        /// @brief タイプをもとに敵を生成する
        void GenerateByType( const status::enemy::Type& type );

        /// @brief 百分率の確率にヒットしたかを取得
        auto HitOfTheTime( const double& chance ) -> bool;

        /// @brief 有効距離内でランダムな位置を取得
        auto RandomPosition() -> Vector2;

       private:
        static constexpr double DECREASE_RATE { 0.9 };  // chainChanceの減少率

        std::vector<LotteryData> lotteryBox {};  // 抽選登録用リスト
        std::vector<LotteryData> box {};  // 本抽選用リスト

        double spawnTimer { 0.0 };
    };
}  // namespace shooting::object

#endif  // !ENEMY_MANAGER_H

// 敵の基底クラス

#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../../Definition/ImageDefinition.h"
#include "../../Manager/ImageManager.h"
#include "ActorBase.h"

namespace shooting::object {
    class EnemyBase : public ActorBase {
       public:
        EnemyBase() = default;

        ~EnemyBase() override = default;

       public:
        /// @brief 敵データの読み込み
        static void LoadEnemyData();
    };
}  // namespace shooting::object

#endif  // !ENEMY_BASE_H

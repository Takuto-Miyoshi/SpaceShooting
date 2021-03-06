// シンプルな敵

#ifndef STANDARD_ENEMY_H
#define STANDARD_ENEMY_H

#include "EnemyBase.h"

namespace shooting::object {
    class StandardEnemy : public EnemyBase {
       public:
        StandardEnemy() = default;

        ~StandardEnemy() override = default;

       public:
        void Update() override;

       protected:
        void Start() override;

       private:
        /// @brief 移動
        void Move();

        /// @brief 射撃
        void Shoot();

       private:
        double shotCount { 0.0 };
    };
}  // namespace shooting::object

#endif  // !STANDARD_ENEMY_H

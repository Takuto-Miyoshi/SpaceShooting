// 死ぬと爆発する敵

#ifndef EXPLODE_ENEMY_H
#define EXPLODE_ENEMY_H

#include "EnemyBase.h"

namespace shooting::object {
    class ExplodeEnemy : public EnemyBase {
       public:
        ExplodeEnemy() = default;

        ~ExplodeEnemy() override = default;

       public:
        void Update() override;

       protected:
        void Start() override;

        void DeathProcess() override;

       private:
        /// @brief 移動
        void Move();

        /// @brief 爆発(拡散弾)
        void Explosion();

       private:
        Vector2 toPlayerVector { 0, 0 };  // プレイヤーの位置
    };
}  // namespace shooting::object

#endif  // !EXPLODE_ENEMY_H

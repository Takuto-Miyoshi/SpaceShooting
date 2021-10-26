// ランダムな方向に攻撃する敵

#ifndef NEEDLE_ENEMY_H
#define NEEDLE_ENEMY_H

#include "EnemyBase.h"

namespace shooting::object {
    class NeedleEnemy : public EnemyBase {
       public:
        NeedleEnemy() = default;

        ~NeedleEnemy() override = default;

       public:
        void Update() override;

       protected:
        void Start() override;

        void Shoot() override;

       private:
        void Move();

       private:
        uint32_t bulletIndex { 0 };  // 発射する数
    };
}  // namespace shooting::object

#endif  // !NEEDLE_ENEMY_H

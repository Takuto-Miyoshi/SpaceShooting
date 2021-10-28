#ifndef GHOST_H
#define GHOST_H

#include "EnemyBase.h"

namespace shooting::object {
    class Ghost : public EnemyBase {
       public:
        Ghost() = default;

        ~Ghost() override = default;

       public:
        void Update() override;

       protected:
        void Start() override;

        void Shoot() override;

       private:
        void Move();

        /// @brief ターゲットの方を向く
        void Look();

       private:
        Vector2<double> target {};  // 追いかける対象

        double transTime { 0.0 };  // Transformまでの時間

        uint32_t wayIndex { 0 };  // wayの数

        float angleOffset { 0.0f };  // way弾の間隔
    };
}  // namespace shooting::object

#endif  // !GHOST_H

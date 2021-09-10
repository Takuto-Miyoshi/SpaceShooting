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

        auto Collide( const ObjectBase& hit ) -> bool override;

       protected:
        void Start() override;

       private:
        void Move();

        void Explosion();

       private:
        Vector2 toPlayerVector { 0, 0 };
    };
}  // namespace shooting::object

#endif  // !EXPLODE_ENEMY_H

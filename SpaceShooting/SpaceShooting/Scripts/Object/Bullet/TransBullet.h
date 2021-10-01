// クラスが変化する弾

#ifndef TRANS_BULLET_H
#define TRANS_BULLET_H

#include <queue>

#include "BulletBase.h"

namespace shooting::object {
    class TransBullet : public ObjectBase {
       public:
        TransBullet() = default;

        ~TransBullet() override = default;

       public:
        void Initialize( BulletBase* transTarget, const status::bullet::TransData& transData );

        void Stack( const status::bullet::TransData& stackData );

        void Update() override;

        void Draw() const override;

       protected:
        void Start() override;

        [[nodiscard]] virtual auto AttackPower() const -> double override;

        [[nodiscard]] virtual auto TakeDamage( const double& attackPower ) -> bool override;

       private:
        double transTime { 0.0 };

        BulletBase* target { nullptr };

        std::queue<status::bullet::TransData> transStack {};
        status::bullet::TransData next {};
    };
}  // namespace shooting::object

#endif  // !TRANS_BULLET_H

// クラスが変化する弾

#ifndef TRANS_BULLET_H
#define TRANS_BULLET_H

#include <queue>

#include "../../Utility/Timer.h"
#include "BulletBase.h"

namespace shooting::object {
    class TransBullet : public ObjectBase {
       public:
        TransBullet() = default;

        ~TransBullet() override = default;

       public:
        void Initialize( BulletBase* transTarget, const status::bullet::TransData& transData ) noexcept;

        void Stack( const status::bullet::TransData& stackData );

        void Update() noexcept override;

        void Draw() const override {}

       protected:
        void Start() override {}

        [[nodiscard]] virtual auto AttackPower() const -> double override { return 0.0; }

        [[nodiscard]] virtual auto TakeDamage( const double& attackPower ) -> bool override { return false; }

       private:
        void Trans();

       private:
        double interval { 0.0 };
        Timer timer { interval, [this]() { Trans(); } };

        BulletBase* target { nullptr };

        std::queue<status::bullet::TransData> transStack {};
        status::bullet::TransData next {};
    };
}  // namespace shooting::object

#endif  // !TRANS_BULLET_H

// 弾の基底クラス

#ifndef BULLET_BASE_H
#define BULLET_BASE_H

#include "../../Definition/StatusDefinition.h"
#include "../../Utility/Property.h"
#include "../../Utility/Timer.h"
#include "../../Utility/Vector.h"
#include "../ObjectBase.h"

namespace shooting::object {
    class BulletBase : public ObjectBase {
       public:
        BulletBase() = default;

        ~BulletBase() override = default;

       public:
        void Initialize( const status::Bullet& bulletData ) noexcept;

        void Update() override;

        void Collide( const ObjectBase& hit ) override;

       protected:
        /// @brief 移動
        virtual void Move() = 0;

        /// @brief その他拡張処理
        virtual void Extention() {};

        /// @brief 向いている方向へ進む
        void MoveToForward();

        /// @brief directionの方向へ進む
        void MoveTo( const Vector2& direction );

        [[nodiscard]] virtual auto AttackPower() const noexcept -> double override;

        [[nodiscard]] virtual auto TakeDamage( const double& attackPower ) noexcept -> bool override;

       protected:
        double interval { status::BulletSetting::LIFE_SPAN_OF_BULLET };
        Timer timer { interval, [this]() { isActive = false; }, false };

        status::Bullet bulletStatus {};
    };
}  // namespace shooting::object

#endif  // !BULLET_BASE_H

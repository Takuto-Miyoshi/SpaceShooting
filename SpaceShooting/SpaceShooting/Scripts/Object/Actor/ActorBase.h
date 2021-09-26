// アクターの基礎クラス

#ifndef ACTOR_BASE_H
#define ACTOR_BASE_H

#include "../ObjectBase.h"

namespace shooting::object {
    class ActorBase : public ObjectBase {
       public:
        ActorBase() = default;

        ~ActorBase() override = default;

       public:
        void Draw() const override;

       protected:
        /// @brief 向いている方向に進む
        void MoveToForward();

        /// @brief directionの方向に進む
        void MoveTo( const Vector2& direction );

        [[nodiscard]] auto AttackPower() const -> double override;

        [[nodiscard]] auto TakeDamage( const double& attackPower ) -> bool override;

       protected:
        status::Actor actorStatus {};
    };
}  // namespace shooting::object

#endif  // !ACTOR_BASE_H

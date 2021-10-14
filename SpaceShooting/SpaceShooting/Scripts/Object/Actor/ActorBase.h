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
        void Update() override;

        void Draw() const override;

       protected:
        void Initialize( const std::string& objectName ) override;

        /// @brief ステータスの更新
        virtual void UpdateStatus() noexcept;

        /// @brief レベルアップ時の処理 @n 基礎ステータスを更新する
        virtual void LevelUp();

        /// @brief 向いている方向に進む
        void MoveToForward();

        /// @brief directionの方向に進む
        void MoveTo( const Vector2& direction );

        [[nodiscard]] auto AttackPower() const noexcept -> double override;

        [[nodiscard]] auto TakeDamage( const double& attackPower ) noexcept -> bool override;

       public:
        ReadonlyProperty<uint32_t> Level { level };

       protected:
        status::Actor actorStatus {};
        status::Actor actorStatusBase {};

        uint32_t level { 0 };  // レベル
    };
}  // namespace shooting::object

#endif  // !ACTOR_BASE_H

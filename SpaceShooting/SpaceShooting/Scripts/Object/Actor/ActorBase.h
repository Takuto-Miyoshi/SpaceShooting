﻿// アクターの基礎クラス

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
        virtual void Initialize( const std::string& imageName, const status::Object& objectData, const status::Actor& actorData );

        /// @brief ステータスの更新
        virtual void UpdateStatus();

        /// @brief レベルアップ時の処理 @n 基礎ステータスを更新する
        virtual void LevelUp();

        /// @brief 向いている方向に進む
        void MoveToForward();

        /// @brief directionの方向に進む
        void MoveTo( const Vector2& direction );

        [[nodiscard]] auto AttackPower() const -> double override;

        [[nodiscard]] auto TakeDamage( const double& attackPower ) -> bool override;

       public:
        ReadonlyProperty<uint32_t> Level { level };

       protected:
        status::Actor actorStatus {};
        status::Actor actorStatusBase {};

        uint32_t level { 0 };  // レベル
    };
}  // namespace shooting::object

#endif  // !ACTOR_BASE_H

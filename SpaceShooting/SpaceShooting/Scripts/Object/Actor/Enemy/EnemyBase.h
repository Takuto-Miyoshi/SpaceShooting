// 敵の基底クラス

#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../../Bullet/BulletBase.h"
#include "../ActorBase.h"

namespace shooting::object {
    class EnemyBase : public ActorBase {
       public:
        EnemyBase() = default;

        ~EnemyBase() override = default;

       public:
        void Update() override;

       protected:
        virtual void Initialize( const std::string& objectName );

        /// @brief expを設定
        virtual void ExpSetting( const int32_t& defaultExp );

        void LevelUp() override;

        virtual void DeathProcess() override;

        virtual void Shoot() = 0;

        /// @brief positionからangleへ弾を発射 @n baseBulletDataをもとにしている
        auto ShootForward() -> BulletBase*;

        /// @brief angleの方向へ発射
        /// @param shootPosition 発射する位置
        auto ShootTo( const Vector2& shootPosition ) -> BulletBase*;

        /// @brief positionから発射
        /// @param shootAngle 発射する方向
        auto ShootTo( const float& shootAngle ) -> BulletBase*;

        /// @brief 弾を発射
        /// @param shootPosition 発射する位置
        /// @param shootAngle 発射する方向
        auto ShootTo( const Vector2& shootPosition, const float& shootAngle ) -> BulletBase*;

       public:
        Property<uint32_t> Level { level };

       protected:
        status::Bullet baseBuletData;

        uint32_t exp { 0 };
        uint32_t expBase { 0 };
        double timer { 0.0 };
        double interval { 0.0 };
    };
}  // namespace shooting::object

#endif  // !ENEMY_BASE_H

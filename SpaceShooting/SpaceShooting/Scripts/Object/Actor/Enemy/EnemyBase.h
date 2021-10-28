// 敵の基底クラス

#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include <string>

#include "../../../Utility/Timer.h"
#include "../../Bullet/BulletBase.h"
#include "../ActorBase.h"

namespace shooting::object {
    class EnemyBase : public ActorBase {
       public:
        EnemyBase() = default;

        ~EnemyBase() override = default;

       protected:
        void Initialize( const std::string& objectName ) override;

        /// @brief expを設定
        virtual void ExpSetting( const int32_t& defaultExp ) noexcept;

        void LevelUp() override;

        virtual void DeathProcess() override;

        virtual void Shoot() = 0;

        /// @brief positionからangleへ弾を発射 @n baseBulletDataをもとにしている
        auto ShootForward() -> BulletBase*;

        /// @brief angleの方向へ発射
        /// @param shootPosition 発射する位置
        auto ShootTo( const Vector2<double>& shootPosition ) -> BulletBase*;

        /// @brief positionから発射
        /// @param shootAngle 発射する方向
        auto ShootTo( const float& shootAngle ) -> BulletBase*;

        /// @brief 弾を発射
        /// @param shootPosition 発射する位置
        /// @param shootAngle 発射する方向
        auto ShootTo( const Vector2<double>& shootPosition, const float& shootAngle ) -> BulletBase*;

       public:
        BasicProperty<uint32_t> Level { level };

       protected:
        status::Bullet baseBuletData;

        uint32_t exp { 0 };
        uint32_t expBase { 0 };

        double interval { 0.0 };
        Timer timer { interval, [this]() { Shoot(); } };
    };
}  // namespace shooting::object

#endif  // !ENEMY_BASE_H

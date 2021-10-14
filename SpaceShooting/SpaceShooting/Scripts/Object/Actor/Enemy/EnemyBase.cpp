#include "EnemyBase.h"

#include "../../../Manager/BulletFactory.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Manager/StatusLoader.h"
#include "../../../Utility/Functions.h"

namespace shooting::object {
    void EnemyBase::Initialize( const std::string& objectName ) {
        ActorBase::Initialize( objectName );

        auto& data { status::StatusLoader::Instance()->Get_a( objectName ) };

        ExpSetting( data.EnemyData.Exp );

        interval = data.EnemyData.Interval;

        baseBuletData = data.BulletData;

        // ステータスが現在のレベルに合うようにする
        for ( auto i { 0u }; i < level; i++ ) {
            LevelUp();
        }

        UpdateStatus();
        actorStatus.HealMax();
    }

    void EnemyBase::ExpSetting( const int32_t& defaultExp ) noexcept {
        expBase = defaultExp + PercentOf<uint32_t>( defaultExp, level * status::ExperienceSetting::RATE_OF_LEVEL_TO_EXP );
        exp = expBase;
    }

    void EnemyBase::LevelUp() {
        ActorBase::LevelUp();
        baseBuletData.LevelUp();
    }

    void EnemyBase::DeathProcess() {
        ObjectManager::Instance()->GiveExp( exp );
    }

    auto EnemyBase::ShootForward() -> BulletBase* {
        return ShootTo( position, angle );
    }

    auto EnemyBase::ShootTo( const Vector2& shootPosition ) -> BulletBase* {
        return ShootTo( shootPosition, angle );
    }

    auto EnemyBase::ShootTo( const float& shootAngle ) -> BulletBase* {
        return ShootTo( position, shootAngle );
    }

    auto EnemyBase::ShootTo( const Vector2& shootPosition, const float& shootAngle ) -> BulletBase* {
        return BulletFactory::Instance()->Create( status::ObjectKind::EnemyBullet, shootPosition, shootAngle, baseBuletData );
    }
}  // namespace shooting::object

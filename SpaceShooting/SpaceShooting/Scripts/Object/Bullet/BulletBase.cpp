#include "BulletBase.h"

#include "../../Definition/StatusDefinition.h"
#include "../../Manager/StatusLoader.h"

namespace shooting::object {
    void BulletBase::Initialize( const status::Bullet& bulletData ) {
        bulletStatus = bulletData;
    }

    void BulletBase::Update() {
        lifeTime += timeManager.lock()->DeltaTime;
        if ( lifeTime >= status::BulletSetting::LIFE_SPAN_OF_BULLET ) [[unlikely]] {
            isActive = false;
        }

        Move();
        Extention();

        bulletStatus.Speed += bulletStatus.Acceleration * timeManager.lock()->DeltaTime;
        angle += bulletStatus.AngularVelocity * timeManager.lock()->DeltaTime;
    }

    void BulletBase::Collide( const ObjectBase& hit ) {
        isActive = false;
        DeathProcess();
    }

    void BulletBase::MoveToForward() {
        ObjectBase::MoveToForward( bulletStatus.Speed );
    }

    void BulletBase::MoveTo( const Vector2& direction ) {
        ObjectBase::MoveTo( direction, bulletStatus.Speed );
    }

    auto BulletBase::AttackPower() const -> double {
        return bulletStatus.AttackPower;
    }

    auto BulletBase::TakeDamage( const double& attackPower ) -> bool {
        return false;
    }
}  // namespace shooting::object

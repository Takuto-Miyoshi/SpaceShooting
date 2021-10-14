#include "BulletBase.h"

#include "../../Manager/StatusLoader.h"

namespace shooting::object {
    void BulletBase::Initialize( const status::Bullet& bulletData ) noexcept {
        bulletStatus = bulletData;

        interval = status::BulletSetting::LIFE_SPAN_OF_BULLET;
    }

    void BulletBase::Update() {
        Move();
        Extention();

        bulletStatus.Speed += bulletStatus.Acceleration * timeManager.lock()->DeltaTime;
        angle += bulletStatus.AngularVelocity * timeManager.lock()->DeltaTime.Cast<float>();
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

    auto BulletBase::AttackPower() const noexcept -> double {
        return bulletStatus.AttackPower;
    }

    auto BulletBase::TakeDamage( const double& attackPower ) noexcept -> bool {
        return false;
    }
}  // namespace shooting::object

#include "BulletBase.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void BulletBase::LoadBulletData() {
        ImageManager::Instance()->LoadGraphHandle( image::STANDARD_BULLET );
    }

    void BulletBase::Initialize( const double& setSpeed, const double& setAttackPower, const double& setAcceleration, const float& setAngularVelocity ) {
        speed = setSpeed;
        attackPower = setAttackPower;
        acceleration = setAcceleration;
        angularVelocity = setAngularVelocity;
    }

    void BulletBase::Update() {
        lifeTime += timeManager.lock()->DeltaTime;
        if ( lifeTime >= status::Bullet::LIFE_SPAN_OF_BULLET ) {
            isActive = false;
        }

        speed += acceleration * timeManager.lock()->DeltaTime;
        angle += angularVelocity * timeManager.lock()->DeltaTime;
    }

    auto BulletBase::Collide( const ObjectBase& hit ) -> bool {
        isActive = false;
        return !isActive;
    }
}  // namespace shooting::object

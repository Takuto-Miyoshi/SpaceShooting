#include "BulletBase.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void BulletBase::LoadBulletData() {
        ImageManager::Instance()->LoadGraphHandle( image::STANDARD_BULLET );
    }

    void BulletBase::Update() {
        lifeTime += timeManager.lock()->DeltaTime;
        if ( lifeTime >= status::Bullet::LIFE_SPAN_OF_BULLET ) {
            isActive = false;
        }
    }

    auto BulletBase::Collide( const ObjectBase& hit ) -> bool {
        isActive = false;
        return !isActive;
    }
}  // namespace shooting::object

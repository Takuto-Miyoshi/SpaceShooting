#include "BulletBase.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void BulletBase::LoadBulletData() {
        ImageManager::Instance()->LoadGraphHandle( image::STANDARD_BULLET );
    }

    void BulletBase::Update() {
        lifeTime += timeManager.lock()->DeltaTime;
        if ( lifeTime >= status::LIFE_SPAN_OF_BULLET ) {
            isActive = false;
        }
    }

    void BulletBase::Collide() {
        isActive = false;
    }
}  // namespace shooting::object

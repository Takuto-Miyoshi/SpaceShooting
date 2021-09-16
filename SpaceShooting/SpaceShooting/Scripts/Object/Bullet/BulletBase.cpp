#include "BulletBase.h"

namespace shooting::object {
    void BulletBase::LoadBulletData() {
        ImageManager::Instance()->LoadGraphHandle( image::STANDARD_BULLET );
    }
}  // namespace shooting::object

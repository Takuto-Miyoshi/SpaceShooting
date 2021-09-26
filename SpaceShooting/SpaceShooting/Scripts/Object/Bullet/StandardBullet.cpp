#include "StandardBullet.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void StandardBullet::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::STANDARD_BULLET.name );

        objectStatus = status::bullet::StandardBullet::OBJECT;
    }

    void StandardBullet::Move() {
        MoveToForward();
    }
}  // namespace shooting::object

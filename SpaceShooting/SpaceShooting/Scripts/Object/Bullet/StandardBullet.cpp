#include "StandardBullet.h"

#include "../../Definition/StatusDefinition.h"

namespace shooting::object {
    void StandardBullet::Start() {
        speed = status::standardBullet::SPEED;
        graphicHandle = ImageManager::Instance()->Image( image::STANDARD_BULLET.name );
    }

    void StandardBullet::Update() {
        position += Vector2::AngleToVector( angle ) * speed * timeManager.lock()->DeltaTime;
    }
}  // namespace shooting::object

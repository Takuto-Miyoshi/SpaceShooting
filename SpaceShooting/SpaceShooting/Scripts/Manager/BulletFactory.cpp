#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

namespace shooting::object {
    void BulletFactory::Create( const status::ObjectKind& objectKind, const status::BulletType& type, const Vector2& position, const float& angle ) {
        switch ( type ) {
            case shooting::object::status::BulletType::StandardBullet:
                ObjectManager::Instance()->CreateObject<StandardBullet>( objectKind, position, angle );
                break;
        }
    }
}  // namespace shooting::object

#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

namespace shooting::object {
    void BulletFactory::Create( const status::ObjectKind& objectKind, const status::bullet::Type& type, const Vector2& position, const float& angle, const status::Bullet& bulletData ) {
        ObjectBase* bullet = nullptr;

        switch ( type ) {
            case shooting::object::status::bullet::Type::StandardBullet:
                bullet = ObjectManager::Instance()->CreateObject<StandardBullet>( objectKind, position, angle );
                break;
            default: return;
        }

        dynamic_cast<BulletBase*>( bullet )->Initialize( bulletData );
    }
}  // namespace shooting::object

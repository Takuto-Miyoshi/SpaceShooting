#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/HomingBullet.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

using namespace shooting::object::status::bullet;

namespace shooting::object {
    void BulletFactory::Create( const status::ObjectKind& objectKind, const status::bullet::Type& type, const Vector2& position, const float& angle, const status::Bullet& bulletData ) {
        ObjectBase* bullet = nullptr;

        switch ( type ) {
            case Type::StandardBullet:
                bullet = CreateBullet<StandardBullet>( objectKind, position, angle );
                break;
            case Type::HomingBullet:
                bullet = CreateBullet<HomingBullet>( objectKind, position, angle );
                break;
            default: return;
        }

        dynamic_cast<BulletBase*>( bullet )->Initialize( bulletData );
    }
}  // namespace shooting::object

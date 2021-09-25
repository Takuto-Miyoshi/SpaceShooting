#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

namespace shooting::object {
    void BulletFactory::Create( const status::ObjectKind& objectKind, const status::BulletType& type, const Vector2& position, const float& angle, const double& speed, const double& attackPower, const double& acceleration, const float& angularVelocity ) {
        BulletBase* bullet = nullptr;
        switch ( type ) {
            case shooting::object::status::BulletType::StandardBullet:
                bullet = dynamic_cast<BulletBase*>( ObjectManager::Instance()->CreateObject<StandardBullet>( objectKind, position, angle ) );
                break;
            default: return;
        }

        bullet->Initialize( speed, attackPower, acceleration, angularVelocity );
    }
}  // namespace shooting::object

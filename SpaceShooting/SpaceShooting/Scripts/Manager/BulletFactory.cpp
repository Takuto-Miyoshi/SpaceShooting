#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

namespace shooting::object {
    void BulletFactory::Initialize() {
        BulletBase::LoadBulletData();
    }

    void BulletFactory::Create( const status::BulletType& type, const Vector2& position, const float& angle ) {
        switch ( type ) {
            case shooting::object::status::BulletType::StandardBullet:
                ObjectManager::Instance()->CreateObject<StandardBullet>( position, angle );
                break;
        }
    }
}  // namespace shooting::object

#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/HomingBullet.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

using namespace shooting::object::status::bullet;

namespace shooting::object {
    auto BulletFactory::Create( const status::ObjectKind& objectKind, const status::bullet::Type& type, const Vector2& position, const float& angle, const status::Bullet& bulletData ) -> BulletBase* {
        ObjectBase* bullet = nullptr;

        switch ( type ) {
            case Type::StandardBullet:
                bullet = CreateBullet<StandardBullet>( objectKind, position, angle );
                break;
            case Type::HomingBullet:
                bullet = CreateBullet<HomingBullet>( objectKind, position, angle );
                break;
            default: return nullptr;
        }

        auto castBullet = dynamic_cast<BulletBase*>( bullet );
        castBullet->Initialize( bulletData );
        return castBullet;
    }

    auto BulletFactory::CreateTrans( BulletBase* transTarget, const status::bullet::TransData& transData ) -> TransBullet* {
        auto bulletTemp = CreateBullet<TransBullet>( transTarget->Kind, Vector2::Zero(), 0.0f );
        auto bullet = dynamic_cast<TransBullet*>( bulletTemp );
        bullet->Initialize( transTarget, transData );
        return bullet;
    }

}  // namespace shooting::object

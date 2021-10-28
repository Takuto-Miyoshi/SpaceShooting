#include "BulletFactory.h"

#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/HomingBullet.h"
#include "../Object/Bullet/StandardBullet.h"
#include "ObjectManager.h"

using namespace shooting::object::status::bullet;

namespace shooting::object {
    auto BulletFactory::Create( const status::ObjectKind& objectKind, const Vector2<double>& position, const float& angle, const status::Bullet& bulletData ) -> BulletBase* {
        auto bullet {
            dynamic_cast<BulletBase*>( [&]() -> ObjectBase* {
                // 弾の種類に応じた弾を作る
                switch (bulletData.BulletType) {
                    case Type::StandardBullet:
                        return CreateBullet<StandardBullet>(objectKind, position, angle);
                    case Type::HomingBullet:
                        return CreateBullet<HomingBullet>(objectKind, position, angle);
                    default: return nullptr;
                } }() )
        };

        bullet->Initialize( bulletData );
        return bullet;
    }

    auto BulletFactory::CreateTrans( BulletBase* transTarget, const status::bullet::TransData& transData ) -> TransBullet* {
        auto bullet { dynamic_cast<TransBullet*>( CreateBullet<TransBullet>( transTarget->Kind, Vector2<double>::Zero<>, 0.0f ) ) };
        bullet->Initialize( transTarget, transData );
        return bullet;
    }

}  // namespace shooting::object

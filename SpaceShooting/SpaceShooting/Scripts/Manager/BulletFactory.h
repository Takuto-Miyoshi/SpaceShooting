// 弾を作成する

#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "../Definition/StatusDefinition.h"
#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/StandardBullet.h"
#include "../Utility/Singleton.h"
#include "ObjectManager.h"

namespace shooting::object {
    class BulletFactory : public Singleton<BulletFactory> {
       public:
        BulletFactory() = default;

        ~BulletFactory() = default;

       public:
        void Initialize() {
            BulletBase::LoadBulletData();
        }

        void Create( status::BulletType type, Vector2 position, float angle ) {
            switch ( type ) {
                case shooting::object::status::BulletType::StandardBullet:
                    objectManager.lock()->CreateObject<StandardBullet>().lock()->Activate( position, angle );
                    break;
            }
        }

       private:
        std::weak_ptr<ObjectManager> objectManager { ObjectManager::Instance() };
    };
}  // namespace shooting::object

#endif  // !BULLET_FACTORY_H

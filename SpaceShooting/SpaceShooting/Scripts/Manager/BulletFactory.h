// 弾を作成する

#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include <memory>

#include "../Definition/StatusDefinition.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.h"

namespace shooting::object {
    class BulletFactory : public Singleton<BulletFactory> {
       public:
        BulletFactory() = default;

        ~BulletFactory() = default;

       public:
        void Initialize();

        void Create( const status::BulletType& type, const Vector2& position, const float& angle );
    };
}  // namespace shooting::object

#endif  // !BULLET_FACTORY_H

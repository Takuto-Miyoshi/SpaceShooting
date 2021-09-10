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
        void Create( const status::ObjectKind& objectKind, const status::BulletType& type, const Vector2& position, const float& angle, const double& speed, const double& attackPower, const double& acceleration = 0.0, const float& angularVelocity = 0.0f );
    };
}  // namespace shooting::object

#endif  // !BULLET_FACTORY_H

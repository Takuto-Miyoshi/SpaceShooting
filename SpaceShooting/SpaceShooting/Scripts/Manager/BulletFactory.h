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
        /// @brief 弾を作成
        /// @param objectKind 属するグループ
        /// @param type 弾の種類
        /// @param position 作成する位置
        /// @param angle 作成する向き
        /// @param bulletData 弾データ
        void Create( const status::ObjectKind& objectKind, const status::bullet::Type& type, const Vector2& position, const float& angle, const status::Bullet& bulletData );
    };
}  // namespace shooting::object

#endif  // !BULLET_FACTORY_H

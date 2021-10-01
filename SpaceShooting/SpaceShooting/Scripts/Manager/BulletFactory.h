// 弾を作成する

#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include <memory>

#include "../Definition/StatusDefinition.h"
#include "../Object/Bullet/BulletBase.h"
#include "../Object/Bullet/TransBullet.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.h"
#include "ObjectManager.h"

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
        auto Create( const status::ObjectKind& objectKind, const status::bullet::Type& type, const Vector2& position, const float& angle, const status::Bullet& bulletData ) -> BulletBase*;

        /// @brief 変化弾を作成
        /// @param transTarget 変化させる弾 @n BulletManager::Createで作成した弾を想定
        /// @param transData 変化データ
        auto CreateTrans( BulletBase* transTarget, const status::bullet::TransData& transData ) -> TransBullet*;

       private:
        template<class T>
        auto CreateBullet( const status::ObjectKind& objectKind, const Vector2& position, const float& angle ) -> ObjectBase* {
            return ObjectManager::Instance()->CreateObject<T>( objectKind, position, angle );
        }
    };
}  // namespace shooting::object

#endif  // !BULLET_FACTORY_H

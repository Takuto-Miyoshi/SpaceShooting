// 弾の基底クラス

#ifndef BULLET_BASE_H
#define BULLET_BASE_H

#include "../../Definition/ImageDefinition.h"
#include "../../Manager/ImageManager.h"
#include "../../Utility/Property.h"
#include "../../Utility/Vector.h"
#include "../ObjectBase.h"

namespace shooting::object {
    class BulletBase : public ObjectBase {
       public:
        BulletBase() = default;

        ~BulletBase() override = default;

       public:
        /// @brief 弾データの読み込み
        static void LoadBulletData();

        void Update() override;

        auto Collide( const ObjectBase& hit ) -> bool override;

       protected:
        double lifeTime { 0.0 };  // 生成されてからの時間
        double speed { 0.0 };  // 弾の移動速度
    };
}  // namespace shooting::object

#endif  // !BULLET_BASE_H

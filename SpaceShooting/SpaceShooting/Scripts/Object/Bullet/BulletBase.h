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
        static void LoadBulletData() {
            // 弾画像を読み込んでおく
            ImageManager::Instance().lock()->LoadGraphHandle( image::standardBullet );
        }

        void Update() override {
            if ( !isActive ) { return; }

            update();
        }

        void Draw() override {
            if ( !isActive ) { return; }

            ObjectBase::Draw();
        }

        void Start() override {
        }

        void Finalize() override {
        }

       protected:
        std::function<void()> update { [] {} };

        double speed { 0.0 };  // 弾の移動速度
    };
}  // namespace shooting::object

#endif  // !BULLET_BASE_H

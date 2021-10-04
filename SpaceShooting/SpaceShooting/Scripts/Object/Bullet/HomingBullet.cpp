#include "HomingBullet.h"

#include "../../Manager/ObjectManager.h"

namespace shooting::object {
    void HomingBullet::Start() {
        graphicHandle = ImageManager::Instance()->Image( image::HOMING_BULLET.name );

        objectStatus = status::bullet::HomingBullet::OBJECT;
    }

    void HomingBullet::Move() {
        auto target = TargetPosition();
        if ( target != Vector2::Zero() ) {
            angle = SLerp<float>( angle, position.AngleTo( target ), status::bullet::HomingBullet::LERP_POWER * timeManager.lock()->DeltaTime );
        }

        MoveToForward();
    }

    auto HomingBullet::TargetPosition() const -> Vector2 {
        auto objectManager = ObjectManager::Instance();

        if ( kind == status::ObjectKind::EnemyBullet ) {
            // 敵の弾ならプレイヤーの位置を返す
            return objectManager->PlayerPosition();
        }

        // それ以外(プレイヤーの弾)なら最寄りの敵の位置を返す
        return objectManager->NearEnemyPosition( position );
    }
}  // namespace shooting::object

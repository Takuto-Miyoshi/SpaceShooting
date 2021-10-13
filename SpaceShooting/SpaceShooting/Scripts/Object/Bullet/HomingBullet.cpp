#include "HomingBullet.h"

#include "../../Definition/StatusLoaderKey.h"
#include "../../Manager/ObjectManager.h"
#include "../../Manager/StatusLoader.h"

namespace shooting::object {
    void HomingBullet::Start() {
        ObjectBase::Initialize( status::loaderKey::object::bullet::HOMING );

        auto& data = status::StatusLoader::Instance()->Get_a( status::loaderKey::object::bullet::HOMING );
        lerpPower = data.ExtraParam1;
    }

    void HomingBullet::Move() {
        auto target = TargetPosition();
        if ( target != Vector2::Zero() ) [[likely]] {
            angle = SLerp<float>( angle, position.AngleTo( target ), lerpPower * timeManager.lock()->DeltaTime );
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

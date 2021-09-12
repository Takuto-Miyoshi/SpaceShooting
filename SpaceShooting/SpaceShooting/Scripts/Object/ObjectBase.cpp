#include "ObjectBase.h"

#include "../Definition/StatusDefinition.h"

namespace shooting::object {
    void ObjectBase::Draw() const {
        DrawRotaGraphFast( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                           static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                           1.0f, angle, graphicHandle, TRUE );

        if ( kind != status::ObjectKind::EnemyBullet && kind != status::ObjectKind::PlayerBullet ) {
            DrawString( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                        static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                        ( std::to_string( static_cast<int32_t>( hp ) ) + "/" + std::to_string( static_cast<int32_t>( maxHp ) ) ).c_str(),
                        GetColor( 255, 255, 255 ) );
        }

        // DEBUG
        DrawCircle( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                    static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                    static_cast<int32_t>( collisionRadius ), GetColor( 0, 255, 0 ), FALSE );
    }
    auto ObjectBase::Collide( const ObjectBase& hit ) -> bool {
        hp -= hit.attackPower;
        if ( hp <= 0 ) { isActive = false; }
        return !isActive;
    }

    void ObjectBase::CheckOutOfValidArea() {
        if ( position.VectorTo( Vector2 { 0, 0 } ).Length() >= Object::VALID_DISTANCE ) {
            OutOfValidArea();
        }
    }

    void ObjectBase::OutOfValidArea() {
        isActive = false;
    }

    void ObjectBase::Activate( const status::ObjectKind& objectKind, const Vector2& resetPosition, const float& resetAngle ) {
        kind = objectKind;
        position = resetPosition;
        angle = resetAngle;
        isActive = true;
    }
}  // namespace shooting::object

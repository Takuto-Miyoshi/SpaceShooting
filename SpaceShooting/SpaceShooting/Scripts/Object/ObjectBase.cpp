#include "ObjectBase.h"

#include "../Definition/StatusDefinition.h"
#include "../Manager/StatusLoader.h"

namespace shooting::object {
    void ObjectBase::Draw() const {
        DrawRotaGraphFast( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                           static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                           1.0f, angle, objectStatus.GraphicHandle, TRUE );

        // DEBUG 当たり判定を表示
        DrawCircle( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                    static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                    static_cast<int32_t>( objectStatus.CollisionRadius ), GetColor( 0, 255, 0 ), FALSE );
    }

    void ObjectBase::Collide( const ObjectBase& hit ) {
        if ( TakeDamage( hit.AttackPower() ) ) {
            isActive = false;
            DeathProcess();
        }
    }

    void ObjectBase::DeathProcess() {
    }

    void ObjectBase::CheckOutOfValidArea() {
        if ( position.To( Vector2<double>::Zero<> ).Length() >= ObjectSetting::VALID_DISTANCE ) {
            OutOfValidArea();
        }
    }

    void ObjectBase::OutOfValidArea() {
        isActive = false;
    }

    void ObjectBase::MoveToForward( const double& speed ) noexcept {
        position += Vector2<>::FromAngle<double>( angle ) * speed * timeManager.lock()->DeltaTime;
    }

    void ObjectBase::MoveTo( const Vector2<double>& direction, const double& speed ) noexcept {
        position += Vector2( direction ) * speed * timeManager.lock()->DeltaTime;
    }

    void ObjectBase::Activate( const status::ObjectKind& objectKind, const Vector2<double>& resetPosition, const float& resetAngle ) noexcept {
        kind = objectKind;
        position = resetPosition;
        angle = resetAngle;
        isActive = true;
    }

    void ObjectBase::Initialize( const std::string& objectName ) {
        auto& data { status::StatusLoader::Instance()->Get_a( objectName ) };
        objectStatusBase = data.ObjectData;
        objectStatus = objectStatusBase;
    }

    void ObjectBase::DrawStringOnHead( std::string&& str, const double&& offsetY, uint32_t&& color ) const noexcept {
        DrawString( position.X.Cast<int32_t>() - camera.lock()->Position->X.Cast<int32_t>(),
                    position.Y.Cast<int32_t>() - camera.lock()->Position->Y.Cast<int32_t>() + static_cast<int32_t>( offsetY ),
                    str.c_str(),
                    color );
    }
}  // namespace shooting::object

#include "ObjectBase.h"

#include "../Definition/StatusDefinition.h"
#include "../Manager/ImageManager.h"

namespace shooting::object {
    void ObjectBase::Draw() const {
        DrawRotaGraphFast( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                           static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                           1.0f, angle, graphicHandle, TRUE );

        // DEBUG
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
        if ( position.To( Vector2::Zero() ).Length() >= ObjectSetting::VALID_DISTANCE ) {
            OutOfValidArea();
        }
    }

    void ObjectBase::OutOfValidArea() {
        isActive = false;
    }

    void ObjectBase::MoveToForward( const double& speed ) {
        position += Vector2::FromAngle( angle ) * speed * timeManager.lock()->DeltaTime;
    }

    void ObjectBase::MoveTo( const Vector2& direction, const double& speed ) {
        position += direction * speed * timeManager.lock()->DeltaTime;
    }

    void ObjectBase::Activate( const status::ObjectKind& objectKind, const Vector2& resetPosition, const float& resetAngle ) {
        kind = objectKind;
        position = resetPosition;
        angle = resetAngle;
        isActive = true;
    }

    void ObjectBase::Initialize( const std::string& imageName, const status::Object& objectData ) {
        graphicHandle = ImageManager::Instance()->Image( imageName );

        objectStatusBase = objectData;
        objectStatus = objectStatusBase;
    }
}  // namespace shooting::object

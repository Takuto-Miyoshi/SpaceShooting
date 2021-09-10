#include "Camera.h"

#include "../Manager/ObjectManager.h"

namespace shooting {
    void Camera::Update() {
        auto pos = object::ObjectManager::Instance()->PlayerPosition();
        position.Set( pos.X - dxlib::SCREEN_SIZE_X / 2,
                      pos.Y - dxlib::SCREEN_SIZE_Y / 2 );
    }

    void Camera::OffsetBy( const Vector2& from ) {
        const Vector2 screenCenter { dxlib::SCREEN_SIZE_X / 2, dxlib::SCREEN_SIZE_Y / 2 };

        auto vector = screenCenter.VectorTo( from );
        auto length = vector.Length();

        if ( length == 0 ) { return; }  // バグ回避
        if ( length >= LENGTH_LIMIT ) { length = LENGTH_LIMIT; }

        length /= SENSITIVITY;

        auto offset = vector.Normalized() * length;
        position += offset;
    }
}  // namespace shooting

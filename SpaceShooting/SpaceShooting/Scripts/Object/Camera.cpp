#include "Camera.h"

#include "../Manager/ObjectManager.h"

namespace shooting {
    void Camera::Update() noexcept {
        const auto pos { object::ObjectManager::Instance()->PlayerPosition() };
        position.Set( pos.X - dxlib::SCREEN_SIZE_X / 2,
                      pos.Y - dxlib::SCREEN_SIZE_Y / 2 );
    }

    void Camera::OffsetBy( const Vector2<double>& from ) noexcept {
        const Vector2<double> screenCenter { dxlib::SCREEN_SIZE_X / 2, dxlib::SCREEN_SIZE_Y / 2 };

        const auto vector { screenCenter.To( from ) };
        auto length { vector.Length() };

        if ( length == 0 ) [[unlikely]] { return; }  // バグ回避
        if ( length >= LENGTH_LIMIT ) { length = LENGTH_LIMIT; }

        length /= SENSITIVITY;

        const auto offset { vector.Normalized() * length };
        position += offset;
    }
}  // namespace shooting

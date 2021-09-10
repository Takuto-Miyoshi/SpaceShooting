// カメラこと座標のオフセット

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "../Definition/DxLibSetting.h"
#include "../Utility/Property.h"
#include "../Utility/Singleton.h"
#include "../Utility/Vector.h"

namespace shooting {
    class Camera : public Singleton<Camera> {
       public:
        Camera() = default;

        ~Camera() = default;

       public:
        void Update() {
            if ( centerTarget ) {
                position.Set( centerTarget->X - dxlib::SCREEN_SIZE_X / 2,
                              centerTarget->Y - dxlib::SCREEN_SIZE_Y / 2 );
            }
        }

        /// @brief fromの位置に応じてカメラをずらす
        void OffsetBy( Vector2 from ) {
            const Vector2 screenCenter { dxlib::SCREEN_SIZE_X / 2, dxlib::SCREEN_SIZE_Y / 2 };

            auto vector = screenCenter.VectorTo( std::move( from ) );
            auto length = vector.Length();

            if ( length == 0 ) { return; }  // バグ回避
            if ( length >= LENGTH_LIMIT ) length = LENGTH_LIMIT;

            length /= SENSITIVITY;

            auto offset = vector.Normalized() * length;
            position += offset;
        }

       public:
        /// @brief カメラの中心にする位置
        Property<std::shared_ptr<Vector2>> CenterTarget { centerTarget };

        /// @brief 位置
        ReadonlyProperty<Vector2> Position { position };

       private:
        static constexpr int32_t LENGTH_LIMIT = 250;  // 上限
        static constexpr double SENSITIVITY = 2.5;  // カーソル感度

        std::shared_ptr<Vector2> centerTarget { nullptr };
        Vector2 position { 0, 0 };
    };
}  // namespace shooting

#endif  // !CAMERA_H

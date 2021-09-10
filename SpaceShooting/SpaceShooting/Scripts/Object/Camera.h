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
        void Update();

        /// @brief fromの位置に応じてカメラをずらす
        void OffsetBy( const Vector2& from );

       public:
        /// @brief 位置
        ReadonlyProperty<Vector2> Position { position };

       private:
        static constexpr int32_t LENGTH_LIMIT = 250;  // 上限
        static constexpr double SENSITIVITY = 2.5;  // カーソル感度

        Vector2 position { 0, 0 };
    };
}  // namespace shooting

#endif  // !CAMERA_H

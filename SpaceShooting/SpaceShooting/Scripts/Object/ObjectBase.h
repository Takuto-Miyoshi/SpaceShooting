// オブジェクトの基礎クラス

#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include <cstdint>

#include "../Manager/TimeManager.h"
#include "../Utility/Vector.h"
#include "Camera.h"
#include "DxLib.h"

namespace shooting::object {
    class ObjectBase {
       public:
        ObjectBase() = default;

        virtual ~ObjectBase() = default;

       public:
        virtual void ReserveStart() {
            if ( !calledOnce ) {
                Start();
                calledOnce = true;
            }
        }

        virtual void Update() = 0;

        virtual void Draw() const {
            DrawRotaGraphFast( static_cast<int32_t>( position.X - camera.lock()->Position->X ),
                               static_cast<int32_t>( position.Y - camera.lock()->Position->Y ),
                               1.0f, angle, graphicHandle, TRUE );
        }

        /// @brief アクティブにする
        /// @param resetPosition アクティブにする位置
        /// @param resetAngle アクティブにする角度
        void Activate( const Vector2& resetPosition, const float& resetAngle );

       public:
        ReadonlyProperty<bool> IsActive { isActive };

       protected:
        virtual void Start() = 0;

       protected:
        std::weak_ptr<TimeManager> timeManager { TimeManager::Instance() };
        std::weak_ptr<Camera> camera { Camera::Instance() };

        bool isActive { false };
        bool calledOnce { false };

        int32_t graphicHandle { 0 };
        Vector2 position { 0, 0 };
        float angle { 0.0f };
    };
}  // namespace shooting::object

#endif  // !OBJECT_BASE_H

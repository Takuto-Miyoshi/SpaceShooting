// オブジェクトの基礎クラス

#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include <cstdint>

#include "../Definition/StatusDefinition.h"
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

        virtual void Draw() const;

        /// @brief 死んだらtrueを返す
        virtual auto Collide( const ObjectBase& hit ) -> bool;

        /// @brief 外に出たらtrueに返す
        void CheckOutOfValidArea();

        /// @brief アクティブにする
        /// @param resetPosition アクティブにする位置
        /// @param resetAngle アクティブにする角度
        void Activate( const status::ObjectKind& objectKind, const Vector2& resetPosition, const float& resetAngle );

       public:
        ReadonlyProperty<bool> IsActive { isActive };

        ReadonlyProperty<status::ObjectKind> Kind { kind };

        ReadonlyProperty<Vector2> Position { position };

        ReadonlyProperty<float> Angle { angle };

        ReadonlyProperty<double> CollisionRadius { collisionRadius };

        Property<double> Speed { speed };

        Property<double> AttackPower { attackPower };

       protected:
        virtual void Start() = 0;

        virtual void OutOfValidArea();

       protected:
        std::weak_ptr<TimeManager> timeManager { TimeManager::Instance() };
        std::weak_ptr<Camera> camera { Camera::Instance() };

        bool isActive { false };
        bool calledOnce { false };

        int32_t graphicHandle { 0 };
        Vector2 position { 0, 0 };
        float angle { 0.0f };
        double collisionRadius { 0.0 };

        double maxHp { 0.0 };
        double hp { maxHp };

        double attackPower { 0.0 };

        double speed { 0.0 };

        status::ObjectKind kind;
    };
}  // namespace shooting::object

#endif  // !OBJECT_BASE_H

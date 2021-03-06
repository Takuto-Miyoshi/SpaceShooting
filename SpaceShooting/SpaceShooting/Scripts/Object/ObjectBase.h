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
        /// @brief Startの呼び出し用
        virtual void ReserveStart() {
            if ( !calledOnce ) {
                Start();
                calledOnce = true;
            }
        }

        /// @brief 更新
        virtual void Update() = 0;

        /// @brief 描画
        virtual void Draw() const;

        /// @brief 当たり判定呼び出し用
        /// @param hit 当たった相手
        virtual void Collide( const ObjectBase& hit );

        /// @brief 有効エリアの外に出たかを調べる
        void CheckOutOfValidArea();

        /// @brief アクティブにする
        /// @param resetPosition アクティブにする位置
        /// @param resetAngle アクティブにする角度
        void Activate( const status::ObjectKind& objectKind, const Vector2& resetPosition, const float& resetAngle );

       protected:
        /// @brief 更新の最初に呼び出される
        virtual void Start() = 0;

        /// @brief HPが0以下になった時にCollideから呼び出される
        virtual void DeathProcess();

        /// @brief 有効エリアの外に出たときにCheckOutOfValidAreaから呼び出される
        virtual void OutOfValidArea();

        /// @brief angleの方向へ進む
        virtual void MoveToForward( const double& speed );

        /// @brief directionの方向へ進む
        virtual void MoveTo( const Vector2& direction, const double& speed );

       public:
        ReadonlyProperty<bool> IsActive { isActive };

        ReadonlyProperty<Vector2> Position { position };

        ReadonlyProperty<float> Angle { angle };

        ReadonlyProperty<status::Object> ObjectStatus { objectStatus };

        ReadonlyProperty<status::ObjectKind> Kind { kind };

       protected:
        /// @brief 攻撃力を取得
        [[nodiscard]] virtual auto AttackPower() const -> double = 0;

        /// @brief ダメージを受ける処理
        /// @return 死亡時にtrue
        [[nodiscard]] virtual auto TakeDamage( const double& attackPower ) -> bool = 0;

       protected:
        std::weak_ptr<TimeManager> timeManager { TimeManager::Instance() };
        std::weak_ptr<Camera> camera { Camera::Instance() };

        bool isActive { false };
        bool calledOnce { false };

        int32_t graphicHandle { 0 };
        Vector2 position { 0, 0 };
        float angle { 0.0f };

        status::Object objectStatus {};

        status::ObjectKind kind {};
    };
}  // namespace shooting::object

#endif  // !OBJECT_BASE_H

// 弾の基底クラス

#ifndef BULLET_BASE_H
#define BULLET_BASE_H

#include "../../Definition/ImageDefinition.h"
#include "../../Manager/ImageManager.h"
#include "../../Utility/Property.h"
#include "../../Utility/Vector.h"
#include "../ObjectBase.h"

namespace shooting::object {
    class BulletBase : public ObjectBase {
       public:
        BulletBase() = default;

        ~BulletBase() override = default;

       public:
        /// @brief 弾データの読み込み
        static void LoadBulletData();

        void Initialize( const status::Bullet& bulletData );

        void Update() override;

        void Collide( const ObjectBase& hit ) override;

       protected:
        /// @brief 移動
        virtual void Move() = 0;

        /// @brief その他拡張処理
        virtual void Extention() {};

        /// @brief 向いている方向へ進む
        void MoveToForward();

        /// @brief directionの方向へ進む
        void MoveTo( const Vector2& direction );

        [[nodiscard]] virtual auto AttackPower() const -> double override;

        [[nodiscard]] virtual auto TakeDamage( const double& attackPower ) -> bool override;

       protected:
        double lifeTime { 0.0 };  // 生成されてからの時間
        status::Bullet bulletStatus {};
    };
}  // namespace shooting::object

#endif  // !BULLET_BASE_H

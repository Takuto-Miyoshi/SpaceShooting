// 武器の基礎クラス

#ifndef WEAPON_BASE_H
#define WEAPON_BASE_H

#include <memory>

#include "../Definition/StatusDefinition.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Bullet/BulletBase.h"
#include "../Utility/Vector.h"

namespace shooting::weapon {
    class WeaponBase {
       public:
        WeaponBase() = default;

        virtual ~WeaponBase() = default;

       public:
        /// @brief 初期化
        /// @param user この武器の使用者
        virtual void Initialize( const object::ActorBase& user, const uint8_t& useRarity );

        /// @brief 更新
        virtual void Update();

        /// @brief 射撃 @n 呼び出し用
        virtual void Shoot();

       protected:
        /// @brief 射撃処理
        virtual void ShootProcess() = 0;

        /// @brief 射撃後の処理
        virtual void ShootedProcess();

        /// @brief 武器データの初期化 @n レア度は事前に設定
        void InitializeWeapon( const std::string& objectName );

        /// @brief 弾ステータスの更新
        virtual void UpdateBulletStatus();

        /// @brief positionからangleへ弾を発射 @n baseBulletDataをもとにしている
        auto ShootForward() -> object::BulletBase*;

        /// @brief angleの方向へ発射
        /// @param shootPosition 発射する位置
        auto ShootTo( const Vector2& shootPosition ) -> object::BulletBase*;

        /// @brief positionから発射
        /// @param shootAngle 発射する方向
        auto ShootTo( const float& shootAngle ) -> object::BulletBase*;

        /// @brief 弾を発射
        /// @param shootPosition 発射する位置
        /// @param shootAngle 発射する方向
        auto ShootTo( const Vector2& shootPosition, const float& shootAngle ) -> object::BulletBase*;

       private:
        /// @brief 所属グループを弾用に変更する
        auto ConvertKind( const object::status::ObjectKind& source ) const -> object::status::ObjectKind;

       protected:
        object::status::Weapon weaponStatus {};

        object::status::Bullet bulletStatus {};
        object::status::Bullet baseBulletData {};

        uint8_t rarity { 0 };

        double timer { 0.0 };
        bool shootable { false };

        Vector2* position { nullptr };
        float* angle { nullptr };
        uint32_t* level { nullptr };
        object::status::ObjectKind kind {};
    };
}  // namespace shooting::weapon

#endif  // !WEAPON_BASE_H

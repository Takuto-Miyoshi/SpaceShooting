// 武器の基礎クラス

#ifndef WEAPON_BASE_H
#define WEAPON_BASE_H

#include <memory>

#include "../Definition/StatusDefinition.h"
#include "../Object/ObjectBase.h"
#include "../Utility/Vector.h"

namespace shooting::weapon {
    class WeaponBase {
       public:
        WeaponBase() = default;

        virtual ~WeaponBase() = default;

       public:
        /// @brief 初期化
        /// @param user この武器の使用者
        virtual void Initialize( const object::ObjectBase& user );

        /// @brief 更新
        virtual void Update();

        /// @brief 射撃 @n 呼び出し用
        virtual void Shoot();

       protected:
        /// @brief 射撃処理
        virtual void ShootProcess() = 0;

        /// @brief 射撃後の処理
        virtual void ShootedProcess();

       private:
        /// @brief 所属グループを弾用に変更する
        auto ConvertKind( const object::status::ObjectKind& source ) const -> object::status::ObjectKind;

       protected:
        object::status::Weapon weaponStatus {};
        double timer { 0.0 };
        bool shootable { false };

        Vector2* position { nullptr };
        float* angle { nullptr };
        object::status::ObjectKind kind {};
    };
}  // namespace shooting::weapon

#endif  // !WEAPON_BASE_H

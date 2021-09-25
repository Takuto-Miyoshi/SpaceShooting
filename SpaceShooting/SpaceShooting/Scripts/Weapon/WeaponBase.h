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
        virtual void Initialize( const object::ObjectBase& user );

        virtual void Update();

        /// @brief 射撃 @n 呼び出し用
        virtual void Shoot();

       protected:
        /// @brief 射撃の内容
        virtual void ShootProcess() = 0;

        /// @brief 射撃後の処理
        virtual void ShootedProcess();

       private:
        auto ConvertKind( const object::status::ObjectKind& source ) const -> object::status::ObjectKind;

       protected:
        double timer { 0.0 };
        double interval { 0.0 };
        bool shootable { false };

        Vector2* position { nullptr };
        float* angle { nullptr };
        object::status::ObjectKind kind {};
    };
}  // namespace shooting::weapon

#endif  // !WEAPON_BASE_H

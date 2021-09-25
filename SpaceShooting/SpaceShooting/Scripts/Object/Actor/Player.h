// プレイヤーの挙動

#ifndef PLAYER_H
#define PLAYER_H

#include "../../Definition/InputDefinition.h"
#include "../../Weapon/WeaponBase.h"
#include "../ObjectBase.h"

namespace shooting::object {
    class Player : public ObjectBase {
       public:
        Player() = default;

        ~Player() override = default;

       public:
        void Update() override;

        auto Collide( const ObjectBase& hit ) -> bool override;

       protected:
        void Start() override;

        void OutOfValidArea() override;

       private:
        void MoveLeft( InputState inputState );

        void MoveRight( InputState inputState );

        void MoveUp( InputState inputState );

        void MoveDown( InputState inputState );

        void Shoot( InputState inputState );

        void LookToCursor();

       private:
        Vector2 previousPosition { 0, 0 };
        std::unique_ptr<weapon::WeaponBase> usingWeapon;
    };
}  // namespace shooting::object

#endif  // !PLAYER_H

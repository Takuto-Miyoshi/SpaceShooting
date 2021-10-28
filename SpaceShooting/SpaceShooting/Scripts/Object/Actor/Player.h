﻿// プレイヤーの挙動

#ifndef PLAYER_H
#define PLAYER_H

#include "../../Definition/InputDefinition.h"
#include "../../Weapon/WeaponBase.h"
#include "ActorBase.h"

namespace shooting::object {
    class Player : public ActorBase {
       public:
        Player() = default;

        ~Player() override = default;

       public:
        void Update() override;

        void Draw() const override;

        void AddExp( const int32_t& exp );

       protected:
        void Start() override;

        void DeathProcess() override;

        void OutOfValidArea() noexcept override;

       private:
        void NextExpSetting() noexcept;

        void MoveLeft( InputState inputState );

        void MoveRight( InputState inputState );

        void MoveUp( InputState inputState );

        void MoveDown( InputState inputState );

        void Shoot( InputState inputState );

        void ChangeWeapon( InputState inputState );

        /// @brief カーソルの方向を向く
        void LookToCursor();

       private:
        Vector2<double> previousPosition { 0, 0 };  //前回の位置

        std::vector<std::shared_ptr<weapon::WeaponBase>> weaponList;
        std::vector<std::shared_ptr<weapon::WeaponBase>>::iterator usingWeapon;

        status::Experience experience;  // 経験値情報
    };
}  // namespace shooting::object

#endif  // !PLAYER_H

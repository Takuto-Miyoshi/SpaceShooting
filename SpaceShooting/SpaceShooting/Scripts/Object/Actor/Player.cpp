#include "Player.h"

#include "../../Definition/StatusDefinition.h"
#include "../../Definition/StatusLoaderKey.h"
#include "../../Manager/InputInvoker.h"
#include "../../Manager/InputManager.h"
#include "../../Utility/Functions.h"
#include "../../Weapon/MachineGun.h"
#include "../../Weapon/StandardRifle.h"

namespace shooting::object {
    void Player::Start() {
        Initialize( status::loaderKey::object::PLAYER );

        weaponList.emplace_back( new weapon::StandardRifle() )->Initialize( *this, status::WeaponSetting::Rare::NORMAL );
        weaponList.emplace_back( new weapon::MachineGun() )->Initialize( *this, status::WeaponSetting::Rare::BROKEN );
        weaponList.emplace_back( new weapon::MachineGun() )->Initialize( *this, status::WeaponSetting::Rare::LEGENDARY );
        usingWeapon = weaponList.begin();

        // 経験値データを初期化
        level = 1;
        NextExpSetting();

        // キー登録
        const auto inputInvoker { InputInvoker::Instance() };
        inputInvoker->RegisterKey(
            KEY_INPUT_A, [this]( InputState inputState ) { MoveLeft( inputState ); }, InputInvoker::Target::Player );
        inputInvoker->RegisterKey(
            KEY_INPUT_D, [this]( InputState inputState ) { MoveRight( inputState ); }, InputInvoker::Target::Player );
        inputInvoker->RegisterKey(
            KEY_INPUT_W, [this]( InputState inputState ) { MoveUp( inputState ); }, InputInvoker::Target::Player );
        inputInvoker->RegisterKey(
            KEY_INPUT_S, [this]( InputState inputState ) { MoveDown( inputState ); }, InputInvoker::Target::Player );
        inputInvoker->RegisterMousebutton(
            MOUSEBUTTON_LEFT, [this]( InputState inputState ) { Shoot( inputState ); }, InputInvoker::Target::Player );
        inputInvoker->RegisterMousebutton(
            MOUSEBUTTON_RIGHT, [this]( InputState inputState ) { ChangeWeapon( inputState ); }, InputInvoker::Target::Player );
    }

    void Player::DeathProcess() {
        InputInvoker::Instance()->UnregisterTarget( InputInvoker::Target::Player );
    }

    void Player::OutOfValidArea() noexcept {
        position = previousPosition;
    }

    void Player::Update() {
        ActorBase::Update();

        LookToCursor();
        usingWeapon->get()->Update();
        previousPosition = position;
    }

    void Player::Draw() const {
        ActorBase::Draw();

        // 経験値表示 DEBUG
        DrawStringOnHead( "EXP:" + std::to_string( experience.Point ) + "/" + std::to_string( experience.Next ), -15.0 );
    }

    void Player::AddExp( const int32_t& exp ) {
        experience.Point += exp;

        if ( level > ObjectSetting::MAX_LEVEL ) { return; }
        // レベルアップ
        while ( experience.Point >= experience.Next ) {
            level++;

            NextExpSetting();

            LevelUp();
        }

        UpdateStatus();
    }

    void Player::NextExpSetting() noexcept {
        experience.Next += ( level + PercentOf<uint32_t>( experience.Next, status::ExperienceSetting::RATE_OF_NEXT_LEVEL ) ) * status::ExperienceSetting::MULTIPLE_OF_NEXT_LEVEL + level;
    }

    void Player::MoveLeft( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2<double>::Left<> );
    }

    void Player::MoveRight( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2<double>::Right<> );
    }

    void Player::MoveUp( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2<double>::Up<> );
    }

    void Player::MoveDown( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2<double>::Down<> );
    }

    void Player::Shoot( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        usingWeapon->get()->Shoot();
    }

    void Player::ChangeWeapon( InputState inputState ) {
        if ( inputState != InputState::Pressed ) { return; }
        usingWeapon++;
        if ( usingWeapon == weaponList.end() ) { usingWeapon = weaponList.begin(); }
    }

    void Player::LookToCursor() {
        const Vector2<> cursorPosition { InputManager::Instance()->CursorPosition + camera.lock()->Position };
        angle = static_cast<float>( position.AngleTo( cursorPosition ) );
    }
}  // namespace shooting::object

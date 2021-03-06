#include "Player.h"

#include "../../Definition/ImageDefinition.h"
#include "../../Definition/StatusDefinition.h"
#include "../../Manager/BulletFactory.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/InputInvoker.h"
#include "../../Manager/InputManager.h"
#include "../../Weapon/StandardRifle.h"
#include "../Bullet/StandardBullet.h"

namespace shooting::object {
    void Player::Start() {
        ImageManager::Instance()->LoadGraphHandle( image::PLAYER );
        graphicHandle = ImageManager::Instance()->Image( image::PLAYER.name );

        objectStatus = status::Player::OBJECT;
        actorStatus = status::Player::ACTOR;

        usingWeapon = std::make_unique<weapon::StandardRifle>();
        usingWeapon->Initialize( *this );

        // キー登録
        auto inputInvoker = InputInvoker::Instance();
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
    }

    void Player::DeathProcess() {
        InputInvoker::Instance()->UnregisterTarget( InputInvoker::Target::Player );
    }

    void Player::OutOfValidArea() {
        position = previousPosition;
    }

    void Player::Update() {
        LookToCursor();
        usingWeapon->Update();
        previousPosition = position;
    }

    void Player::MoveLeft( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2::Left() );
    }

    void Player::MoveRight( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2::Right() );
    }

    void Player::MoveUp( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2::Up() );
    }

    void Player::MoveDown( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        MoveTo( Vector2::Down() );
    }

    void Player::Shoot( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        usingWeapon->Shoot();
    }

    void Player::LookToCursor() {
        auto&& cursorPosition = InputManager::Instance()->CursorPosition + camera.lock()->Position;
        angle = static_cast<float>( position.AngleTo( cursorPosition ) );
    }
}  // namespace shooting::object

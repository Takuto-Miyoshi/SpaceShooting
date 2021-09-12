#include "Player.h"

#include "../../Definition/ImageDefinition.h"
#include "../../Definition/StatusDefinition.h"
#include "../../Manager/BulletManager.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/InputInvoker.h"
#include "../../Manager/InputManager.h"
#include "../ObjectBase.h"

namespace shooting::object {
    void Player::Update() {
        LookToCursor();
    }

    void Player::Finalize() {
    }

    void Player::Start() {
        ImageManager::Instance().lock()->LoadGraphHandle( image::player );
        graphicHandle = ImageManager::Instance().lock()->Image( image::player.name );

        // キー登録
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_A, [this]( InputState inputState ) { MoveLeft( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_D, [this]( InputState inputState ) { MoveRight( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_W, [this]( InputState inputState ) { MoveUp( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_S, [this]( InputState inputState ) { MoveDown( inputState ); } );
        InputInvoker::Instance().lock()->RegisterMousebutton( MOUSEBUTTON_LEFT, [this]( InputState inputState ) { Shoot( inputState ); } );

        camera.lock()->CenterTarget = std::make_shared<Vector2>( position );
    }

    void Player::MoveLeft( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.X -= status::player::SPEED * timeManager.lock()->DeltaTime;
    }

    void Player::MoveRight( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.X += status::player::SPEED * timeManager.lock()->DeltaTime;
    }

    void Player::MoveUp( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.Y -= status::player::SPEED * timeManager.lock()->DeltaTime;
    }

    void Player::MoveDown( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.Y += status::player::SPEED * timeManager.lock()->DeltaTime;
    }

    void Player::Shoot( InputState inputState ) {
        if ( inputState != InputState::Pressed ) { return; }
        BulletManager::Instance().lock()->Generate( status::BulletType::StandardBullet, position, angle );
    }

    void Player::LookToCursor() {
        auto cursorPosition = InputManager::Instance().lock()->CursorPosition + camera.lock()->Position;
        angle = static_cast<float>( position.Angle( cursorPosition, true ) );
    }
}  // namespace shooting::object

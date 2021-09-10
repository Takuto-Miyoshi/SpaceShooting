#include "Player.h"

#include "../../Definition/ImageDefinition.h"
#include "../../Definition/StatusDefinition.h"
#include "../../Manager/InputInvoker.h"
#include "../../Manager/InputManager.h"
#include "../ObjectBase.h"

namespace shooting::object::actor {
    void Player::Update() {
        LookToCursor();
    }

    void Player::Finalize() {
    }

    void Player::Start() {
        graphicHandle = LoadGraph( image::PLAYER_PATH.c_str() );

        // キー登録
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_A, [this]( InputState inputState ) { MoveLeft( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_D, [this]( InputState inputState ) { MoveRight( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_W, [this]( InputState inputState ) { MoveUp( inputState ); } );
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_S, [this]( InputState inputState ) { MoveDown( inputState ); } );
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

    void Player::LookToCursor() {
        auto cursorPosition = InputManager::Instance().lock()->CursorPosition + camera.lock()->Position;
        angle = static_cast<float>( position.Angle( cursorPosition, true ) );
    }
}  // namespace shooting::object::actor

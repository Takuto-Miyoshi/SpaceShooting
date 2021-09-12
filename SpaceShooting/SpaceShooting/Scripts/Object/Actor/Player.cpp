#include "Player.h"

#include "../../Definition/ImageDefinition.h"
#include "../../Definition/StatusDefinition.h"
#include "../../Manager/BulletFactory.h"
#include "../../Manager/ImageManager.h"
#include "../../Manager/InputInvoker.h"
#include "../../Manager/InputManager.h"
#include "../Bullet/StandardBullet.h"

namespace shooting::object {
    void Player::Start() {
        ImageManager::Instance()->LoadGraphHandle( image::PLAYER );
        graphicHandle = ImageManager::Instance()->Image( image::PLAYER.name );
        collisionRadius = status::Player::COLLISION_RADIUS;
        maxHp = status::Player::MAX_HP;
        hp = maxHp;
        speed = status::Player::SPEED;

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

    void Player::OutOfValidArea() {
        position = previousPosition;
    }

    void Player::Update() {
        LookToCursor();
        previousPosition = position;
    }

    auto Player::Collide( const ObjectBase& hit ) -> bool {
        if ( ObjectBase::Collide( hit ) ) {
            InputInvoker::Instance()->UnregisterTarget( InputInvoker::Target::Player );
        }
        return !isActive;
    }

    void Player::MoveLeft( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.X -= speed * timeManager.lock()->DeltaTime;
    }

    void Player::MoveRight( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.X += speed * timeManager.lock()->DeltaTime;
    }

    void Player::MoveUp( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.Y -= speed * timeManager.lock()->DeltaTime;
    }

    void Player::MoveDown( InputState inputState ) {
        if ( inputState != InputState::Hold ) { return; }
        position.Y += speed * timeManager.lock()->DeltaTime;
    }

    void Player::Shoot( InputState inputState ) {
        if ( inputState != InputState::Pressed ) { return; }
        BulletFactory::Instance()->Create( status::ObjectKind::PlayerBullet, status::BulletType::StandardBullet, position, angle );
    }

    void Player::LookToCursor() {
        auto cursorPosition = InputManager::Instance()->CursorPosition + camera.lock()->Position;
        angle = static_cast<float>( position.Angle( cursorPosition, true ) );
    }
}  // namespace shooting::object

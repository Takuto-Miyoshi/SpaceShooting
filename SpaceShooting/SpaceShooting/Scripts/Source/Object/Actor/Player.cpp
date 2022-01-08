
#include <Game/InputInvoker.hpp>
#include <Game/InputManager.hpp>
#include <Game/Object/Actor/Player.hpp>

namespace game {
    Player::Player() {
        auto& invoker { InputInvoker::Instance() };
        invoker->Regist( MOVE_REGIST_NAME, { MOVE_UP, InputState::Hold, [this]() { MoveUp(); } } );
        invoker->Regist( MOVE_REGIST_NAME, { MOVE_DOWN, InputState::Hold, [this]() { MoveDown(); } } );
        invoker->Regist( MOVE_REGIST_NAME, { MOVE_LEFT, InputState::Hold, [this]() { MoveLeft(); } } );
        invoker->Regist( MOVE_REGIST_NAME, { MOVE_RIGHT, InputState::Hold, [this]() { MoveRight(); } } );
    }

    void Player::SetDefault() {
        object = ObjectData {
            .TexturePath { "Textures/Object/Actor/Player.png" },
            .TextureName { "Player" }
        };
    }

    constexpr void game::Player::MoveUp() {
        transform.Position->Y.Add();
    }

    constexpr void game::Player::MoveDown() {
        transform.Position->Y.Add();
    }

    constexpr void game::Player::MoveLeft() {
        transform.Position->X.Add();
    }

    constexpr void game::Player::MoveRight() {
        transform.Position->X.Add();
    }

    void Player::LookToCursor() {
        //auto& cursor { InputManager::Instance()->CursorPosition.Get() };
        //transform.Direction = transform.Position->To( cursor );
    }
}  // namespace game

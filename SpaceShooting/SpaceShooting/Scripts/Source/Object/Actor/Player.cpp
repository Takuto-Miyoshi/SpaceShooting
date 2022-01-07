
#include <Game/InputInvoker.hpp>
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

    void game::Player::MoveUp() {
        transform.Position->Y--;
    }

    void game::Player::MoveDown() {
        transform.Position->Y++;
    }

    void game::Player::MoveLeft() {
        transform.Position->X--;
    }

    void game::Player::MoveRight() {
        transform.Position->X++;
    }
}  // namespace game

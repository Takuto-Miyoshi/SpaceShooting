
// プレイヤー

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <DxLib.h>

#include <Game/Object/ObjectBase.hpp>

namespace game {
    class Player final : public ObjectBase {
       public:
        Player();

        ~Player() override = default;

       protected:
        void SetDefault() override;

       private:
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

       private:
        static constexpr std::string_view MOVE_REGIST_NAME { "PlayerMovement" };
        static constexpr auto MOVE_UP { KEY_INPUT_W };
        static constexpr auto MOVE_DOWN { KEY_INPUT_S };
        static constexpr auto MOVE_LEFT { KEY_INPUT_A };
        static constexpr auto MOVE_RIGHT { KEY_INPUT_D };
    };
}  // namespace game

#endif  // !PLAYER_HPP

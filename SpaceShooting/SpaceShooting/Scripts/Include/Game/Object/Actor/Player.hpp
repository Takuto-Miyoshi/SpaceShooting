
// プレイヤー

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <DxLib.h>

#include <Game/Object/ObjectBase.hpp>

namespace game {
    class Player final : public ObjectBase {
       public:
        Player() = default;

        ~Player() override = default;

       protected:
        void SetDefault() override;

       private:
        static constexpr auto MOVE_UP { KEY_INPUT_W };
        static constexpr auto MOVE_DOWN { KEY_INPUT_S };
        static constexpr auto MOVE_LEFT { KEY_INPUT_A };
        static constexpr auto MOVE_RIGHT { KEY_INPUT_D };
    };
}  // namespace game

#endif  // !PLAYER_HPP

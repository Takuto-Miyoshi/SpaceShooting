
#include <Game/Object/Actor/Player.hpp>

namespace game {
    void Player::SetDefault() {
        object = ObjectData {
            .TexturePath { "Textures/Object/Actor/Player.png" },
            .TextureName { "Player" }
        };
    }
}  // namespace game


// ゲームシーン

#ifndef IN_GAME_HPP
#define IN_GAME_HPP

#include <Game/IScene.hpp>

namespace game::scene {
    class InGame final : public IScene {
       public:
        InGame() = default;

        ~InGame() override = default;

       public:
        void Initialize() override;

        void Update() override;

        void Draw() override;

        void Finalize() override;
    };
}  // namespace game::scene

#endif  // !IN_GAME_HPP

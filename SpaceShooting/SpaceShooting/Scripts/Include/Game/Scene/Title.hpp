
// タイトルシーン

#ifndef TITLE_HPP
#define TITLE_HPP

#include <Game/IScene.hpp>

namespace game::scene {
    class Title final : public IScene {
       public:
        Title() = default;

        ~Title() override = default;

       public:
        void Initialize() override;

        void Update() override;

        void Draw() override;

        void Finalize() override;
    };
}  // namespace game::scene

#endif  // !TITLE_HPP

// タイトル画面

#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "SceneBase.h"

namespace shooting::scene {
    class TitleScene : public SceneBase {
       public:
        TitleScene() = default;

        ~TitleScene() override = default;

       public:
        void Start() override;

        void Update() noexcept override;

        void Draw() noexcept override;

        void Finalize() noexcept override;
    };
}  // namespace shooting::scene

#endif  // !TITLE_SCENE_H

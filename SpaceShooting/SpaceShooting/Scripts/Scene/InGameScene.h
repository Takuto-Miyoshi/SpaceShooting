// ゲームプレイ画面

#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "SceneBase.h"

namespace shooting::scene {
    class InGameScene : public SceneBase {
       public:
        InGameScene() = default;

        ~InGameScene() = default;

       public:
        void Start() override;

        void Update() override;

        void Draw() override;

        void Finalize() override;
    };
}  // namespace shooting::scene

#endif  // !IN_GAME_SCENE_H

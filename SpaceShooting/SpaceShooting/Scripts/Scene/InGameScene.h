// ゲームプレイ画面

#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include <vector>

#include "../Manager/BulletManager.h"
#include "../Object/ObjectBase.h"
#include "SceneBase.h"

namespace shooting::scene {
    class InGameScene : public SceneBase {
       public:
        InGameScene() = default;

        ~InGameScene() override = default;

       public:
        void Start() override;

        void Update() override;

        void Draw() override;

        void Finalize() override;

       private:
        std::weak_ptr<object::BulletManager> bulletManager { object::BulletManager::Instance() };
        std::vector<std::unique_ptr<object::ObjectBase>> objectList {};
    };
}  // namespace shooting::scene

#endif  // !IN_GAME_SCENE_H

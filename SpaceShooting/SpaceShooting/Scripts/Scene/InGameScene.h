// ゲームプレイ画面

#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include <memory>

#include "../Manager/EnemyManager.h"
#include "../Manager/ObjectManager.h"
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

        void Finalize() noexcept override;

       private:
        std::weak_ptr<object::ObjectManager> objectManager { object::ObjectManager::Instance() };
        object::EnemyManager enemyManager { object::EnemyManager() };
    };
}  // namespace shooting::scene

#endif  // !IN_GAME_SCENE_H

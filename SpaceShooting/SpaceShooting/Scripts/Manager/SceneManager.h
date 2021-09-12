// シーンの実行と変更を管理

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Scene/SceneBase.h"
#include "../Utility/Property.h"
#include "InputInvoker.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace shooting {
    class SceneManager {
       public:
        SceneManager() = default;

        ~SceneManager() = default;

       public:
        void Initialize();

        void Update();

       private:
        void ChangeScene( const scene::SceneDefs& next );

       public:
        /// @brief ゲームを終了する
        ReadonlyProperty<bool> EndGame { endGame };

       private:
        std::weak_ptr<InputManager> inputManager { InputManager::Instance() };
        std::weak_ptr<InputInvoker> inputInvoker { InputInvoker::Instance() };
        std::weak_ptr<TimeManager> timeManager { TimeManager::Instance() };

        std::unique_ptr<scene::SceneBase> currentScene;  // 現在取り扱っているシーン

        bool endGame { false };  // ゲームを終了するか
    };
}  // namespace shooting

#endif  // !SCENE_MANAGER_H

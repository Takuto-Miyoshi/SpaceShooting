// シーンの実行と変更を管理

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Scene/SceneBase.h"
#include "../Utility/Property.h"
#include "../Utility/Singleton.h"
#include "InputInvoker.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace shooting {
    class SceneManager : public Singleton<SceneManager> {
       public:
        SceneManager() = default;

        ~SceneManager() = default;

       public:
        void Initialize();

        void Update();

        void Finalize();

       private:
        void ChangeScene( scene::SceneDefs next );

       public:
        /// @brief ゲームを終了する
        ReadonlyProperty<bool> EndGame { endGame };

       private:
        std::weak_ptr<InputManager> inputManager;
        std::weak_ptr<InputInvoker> inputInvoker;
        std::weak_ptr<TimeManager> timeManager;

        std::unique_ptr<scene::SceneBase> currentScene;  // 現在取り扱っているシーン

        bool endGame { false };  // ゲームを終了するか
    };
}  // namespace shooting

#endif  // !SCENE_MANAGER_H

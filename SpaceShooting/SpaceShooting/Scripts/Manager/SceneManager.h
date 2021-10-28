// シーンの実行と変更を管理

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Scene/SceneBase.h"
#include "../Utility/Property.hpp"
#include "InputInvoker.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace shooting {
    class SceneManager {
       public:
        SceneManager() = default;

        ~SceneManager() = default;

       public:
        /// @brief 初期化
        void Initialize();

        /// @brief 更新
        void Update();

       private:
        /// @brief 実行するシーンを変更する
        void ChangeScene( const scene::SceneDefs& next );

       public:
        /// @brief ゲームを終了するか
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

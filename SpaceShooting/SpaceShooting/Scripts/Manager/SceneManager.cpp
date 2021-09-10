#include "SceneManager.h"

#include <memory>

#include "../Scene/InGameScene.h"
#include "../Scene/TitleScene.h"

namespace shooting {
    void SceneManager::Initialize() {
        inputManager = InputManager::Instance();
        inputManager.lock()->Initialize();

        inputInvoker = InputInvoker::Instance();
        inputInvoker.lock()->Initialize();

        timeManager = TimeManager::Instance();
        timeManager.lock()->Initialize();

        ChangeScene( scene::SceneDefs::Title );
    }

    void SceneManager::Update() {
        timeManager.lock()->Update();

        inputManager.lock()->Update();

        currentScene->Update();
        inputInvoker.lock()->Update();

        currentScene->Draw();

        endGame = currentScene->EndGame;
        if ( currentScene->Change ) { ChangeScene( currentScene->NextScene ); }
    }

    void SceneManager::Finalize() {
        timeManager.lock()->Finalize();
        inputInvoker.lock()->Finalize();
        inputManager.lock()->Finalize();
        Singleton::Finalize();
    }

    void SceneManager::ChangeScene( scene::SceneDefs next ) {
        inputInvoker.lock()->Reset();
        if ( currentScene ) { currentScene->Finalize(); }

        switch ( next ) {
            case scene::SceneDefs::Title:
                currentScene = std::make_unique<scene::TitleScene>();
                break;
            case scene::SceneDefs::InGame:
                currentScene = std::make_unique<scene::InGameScene>();
                break;
            default: endGame = true; break;
        }

        currentScene->Start();
    }
}  // namespace shooting

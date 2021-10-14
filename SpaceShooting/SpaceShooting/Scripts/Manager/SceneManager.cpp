#include "SceneManager.h"

#include <memory>

#include "../Scene/InGameScene.h"
#include "../Scene/TitleScene.h"

namespace shooting {
    void SceneManager::Initialize() {
        inputInvoker.lock()->Initialize();
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
        if ( currentScene->Change ) [[unlikely]] { ChangeScene( currentScene->NextScene ); }
    }

    void SceneManager::ChangeScene( const scene::SceneDefs& next ) {
        inputInvoker.lock()->Reset();
        timeManager.lock()->ResetTimerList();

        if ( currentScene ) [[likely]] { currentScene->Finalize(); }

        switch ( next ) {
            case scene::SceneDefs::Title: currentScene = std::make_unique<scene::TitleScene>(); break;
            case scene::SceneDefs::InGame: currentScene = std::make_unique<scene::InGameScene>(); break;
            default: endGame = true; break;
        }

        currentScene->Start();
    }
}  // namespace shooting

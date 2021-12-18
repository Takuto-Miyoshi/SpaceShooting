
#include <DxLib.h>

#include <Game/InputManager.hpp>
#include <Game/Scene/InGame.hpp>
#include <Game/SceneManager.hpp>

namespace game::scene {
    void InGame::Initialize() {
    }

    void InGame::Update() {
        printfDx( "CurrentScene : InGame\n" );

        if ( InputManager::Instance()->KeyState( KEY_INPUT_SPACE ) == InputState::Pressed ) {
            SceneManager::Instance()->ChangeScene( "Title" );
        }
    }

    void InGame::Draw() {
    }

    void InGame::Finalize() {
    }
}  // namespace game::scene


#include <DxLib.h>

#include <Game/InputManager.hpp>
#include <Game/Scene/Title.hpp>
#include <Game/SceneManager.hpp>

namespace game::scene {
    void Title::Initialize() {
    }

    void Title::Update() {
        printfDx( "CurrentScene : Title\n" );

        if ( InputManager::Instance()->KeyState( KEY_INPUT_SPACE ) == InputState::Pressed ) {
            SceneManager::Instance()->ChangeScene( "InGame" );
        }
    }

    void Title::Draw() {
    }

    void Title::Finalize() {
    }
}  // namespace game::scene

#include "InGameScene.h"

#include "../Manager/InputInvoker.h"
#include "DxLib.h"

namespace shooting::scene {
    void InGameScene::Start() {
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_SPACE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::Title ); }
        } );
    }

    void InGameScene::Update() {
    }

    void InGameScene::Draw() {
        printfDx( "InGame" );
    }

    void InGameScene::Finalize() {
    }
}  // namespace shooting::scene

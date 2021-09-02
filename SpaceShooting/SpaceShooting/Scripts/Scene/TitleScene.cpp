#include "TitleScene.h"

#include "../Manager/InputInvoker.h"
#include "DxLib.h"

namespace shooting::scene {
    void TitleScene::Start() {
        // ゲーム終了キーを登録
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_ESCAPE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { EndGame = true; }
        } );

        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_RETURN, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::InGame ); }
        } );
    }

    void TitleScene::Update() {
    }

    void TitleScene::Draw() {
        printfDx( "Title" );
    }

    void TitleScene::Finalize() {
    }
}  // namespace shooting::scene

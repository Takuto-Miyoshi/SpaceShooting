#include "InGameScene.h"

#include "../Manager/ImageManager.h"
#include "../Manager/InputInvoker.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/Player.h"
#include "../Object/Camera.h"
#include "DxLib.h"

using shooting::object::status::ObjectKind;

namespace shooting::scene {
    void InGameScene::Start() {
        // キー登録
        InputInvoker::Instance()->RegisterKey( KEY_INPUT_SPACE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::Title ); }
        } );

        objectManager.lock()->Initialize();
        objectManager.lock()->CreateObject<object::Player>( ObjectKind::Player );
    }

    void InGameScene::Update() {
        objectManager.lock()->Update();

        Camera::Instance()->Update();
        Camera::Instance()->OffsetBy( InputManager::Instance()->CursorPosition );
    }

    void InGameScene::Draw() {
        objectManager.lock()->Draw();

        printfDx( "InGame" );
    }

    void InGameScene::Finalize() {
        objectManager.lock()->Finalize();
    }
}  // namespace shooting::scene

#include "InGameScene.h"

#include <algorithm>

#include "../Manager/BulletFactory.h"
#include "../Manager/InputInvoker.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/Player.h"
#include "../Object/Camera.h"
#include "DxLib.h"

namespace shooting::scene {
    void InGameScene::Start() {
        // キー登録
        InputInvoker::Instance().lock()->RegisterKey( KEY_INPUT_SPACE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::Title ); }
        } );

        object::BulletFactory().Instance().lock()->Initialize();

        objectManager.lock()->Initialize();
        objectManager.lock()->CreateObject<object::Player>();
    }

    void InGameScene::Update() {
        objectManager.lock()->Update();

        Camera::Instance().lock()->Update();
        Camera::Instance().lock()->OffsetBy( InputManager::Instance().lock()->CursorPosition );
    }

    void InGameScene::Draw() {
        objectManager.lock()->Draw();

        printfDx( "InGame" );
    }

    void InGameScene::Finalize() {
        objectManager.lock()->Finalize();
    }
}  // namespace shooting::scene

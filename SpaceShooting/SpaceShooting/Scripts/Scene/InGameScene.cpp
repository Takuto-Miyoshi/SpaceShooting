#include "InGameScene.h"

#include <algorithm>

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

        // オブジェクト
        objectList = std::vector<std::unique_ptr<object::ObjectBase>> {};
        objectList.push_back( std::make_unique<object::actor::Player>() );
    }

    void InGameScene::Update() {
        std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
            element->ReserveStart();
            element->Update();
        } );

        Camera::Instance().lock()->Update();
        Camera::Instance().lock()->OffsetBy( InputManager::Instance().lock()->CursorPosition );
    }

    void InGameScene::Draw() {
        std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
            element->Draw();
        } );

        printfDx( "InGame" );
    }

    void InGameScene::Finalize() {
        std::for_each( objectList.begin(), objectList.end(), []( auto& element ) {
            element->Finalize();
        } );
    }
}  // namespace shooting::scene

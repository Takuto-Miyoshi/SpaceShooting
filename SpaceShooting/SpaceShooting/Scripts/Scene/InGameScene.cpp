#include "InGameScene.h"

#include "../Definition/StatusDefinition.h"
#include "../Manager/InputInvoker.h"
#include "../Manager/InputManager.h"
#include "../Manager/StatusLoader.h"
#include "../Object/Actor/Player.h"
#include "../Object/Camera.h"
#include "DxLib.h"

using namespace shooting::object;
using shooting::object::status::ObjectKind;

namespace shooting::scene {
    void InGameScene::Start() {
        status::StatusLoader::Instance()->Load();

        // キー登録
        InputInvoker::Instance()->RegisterKey( KEY_INPUT_SPACE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::Title ); }
        } );

        objectManager.lock()->Initialize();
        objectManager.lock()->CreateObject<Player>( ObjectKind::Player );

        enemyManager.Initialize();
        enemyManager.UseGroup = 1;
    }

    void InGameScene::Update() {
        objectManager.lock()->Update();

        const auto& camera { Camera::Instance() };
        camera->Update();
        camera->OffsetBy( InputManager::Instance()->CursorPosition );
    }

    void InGameScene::Draw() {
        objectManager.lock()->Draw();

        // DEBUG 有効範囲を表示
        DrawCircle( -Camera::Instance()->Position->X.Cast<int32_t>(),
                    -Camera::Instance()->Position->Y.Cast<int32_t>(),
                    static_cast<int32_t>( object::ObjectSetting::VALID_DISTANCE ),
                    GetColor( 255, 0, 0 ),
                    FALSE );

        printfDx( "InGame" );
    }

    void InGameScene::Finalize() noexcept {
        objectManager.lock()->Finalize();
    }
}  // namespace shooting::scene

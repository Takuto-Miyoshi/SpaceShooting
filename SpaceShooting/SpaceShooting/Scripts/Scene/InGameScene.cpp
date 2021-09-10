#include "InGameScene.h"

#include "../Definition/StatusDefinition.h"
#include "../Manager/ImageManager.h"
#include "../Manager/InputInvoker.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/Player.h"
#include "../Object/Camera.h"
#include "DxLib.h"

using namespace shooting::object::status;
using shooting::object::status::ObjectKind;

namespace shooting::scene {
    void InGameScene::Start() {
        // キー登録
        InputInvoker::Instance()->RegisterKey( KEY_INPUT_SPACE, [this]( InputState inputState ) {
            if ( inputState == InputState::Pressed ) { ChangeScene( SceneDefs::Title ); }
        } );

        objectManager.lock()->Initialize();
        objectManager.lock()->CreateObject<object::Player>( ObjectKind::Player );

        enemyManager.Initialize();
        enemyManager.Register( object::EnemyManager::EnemyType::StandardEnemy, StandardEnemy::SPAWN_RATE, StandardEnemy::CHAIN_RATE );
        enemyManager.Register( object::EnemyManager::EnemyType::ExplodeEnemy, ExplodeEnemy::SPAWN_RATE, ExplodeEnemy::CHAIN_RATE );
    }

    void InGameScene::Update() {
        enemyManager.Update();
        objectManager.lock()->Update();

        Camera::Instance()->Update();
        Camera::Instance()->OffsetBy( InputManager::Instance()->CursorPosition );
    }

    void InGameScene::Draw() {
        objectManager.lock()->Draw();

        // DEBUG
        DrawCircle( static_cast<int32_t>( -Camera::Instance()->Position->X ),
                    static_cast<int32_t>( -Camera::Instance()->Position->Y ),
                    static_cast<int32_t>( object::Object::VALID_DISTANCE ),
                    GetColor( 255, 0, 0 ),
                    FALSE );

        printfDx( "InGame" );
    }

    void InGameScene::Finalize() {
        objectManager.lock()->Finalize();
    }
}  // namespace shooting::scene

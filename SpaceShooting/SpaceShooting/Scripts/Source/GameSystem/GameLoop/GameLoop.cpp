
#include <DxLib.h>

#include <Game/Exception.hpp>
#include <Game/GameLoop.hpp>
#include <Game/InputManager.hpp>
#include <Game/Scene/InGame.hpp>
#include <Game/Scene/Title.hpp>
#include <Game/SceneManager.hpp>
#include <Game/TimeManager.hpp>
#include <chrono>

using namespace std::chrono_literals;

namespace game {
    GameLoop::GameLoop( const DxLibConfig& config ) {
        DxInitialize( config );
        targetFPS = config.FrameRate;
    }

    GameLoop::~GameLoop() {
        DxFinalize();
    }

    void GameLoop::Exec() {
        auto inputManager { InputManager::Instance() };
        auto timeManager { TimeManager::Instance() };
        auto sceneManager { SceneManager::Instance() };

        sceneManager->Regist<scene::Title>( "Title" );
        sceneManager->Regist<scene::InGame>( "InGame" );

        while ( true ) {
            if ( ProcessMessage() == FAIL ) { break; }

            ClearDrawScreen();
            clsDx();

            inputManager->Update();
            timeManager->Update();
            sceneManager->Update();
            if ( sceneManager->EndGame() ) { break; }

            timeManager->MarkFPS( targetFPS );

            printfDx( "FPS : %d\n", timeManager->FPS() );
            printfDx( "DeltaTime : %f\n", timeManager->DeltaTime() );

            ScreenFlip();
        }
    }

    void GameLoop::DxInitialize( const DxLibConfig& config ) {
        SetOutApplicationLogValidFlag( FALSE );
        ChangeWindowMode( static_cast<int32_t>( !config.EnableFullscreen ) );
        SetGraphMode( config.ScreenSize.Width, config.ScreenSize.Height, config.ColorBitDepth, config.FrameRate );
        SetMainWindowText( config.WindowName.c_str() );
        SetWaitVSyncFlag( static_cast<int32_t>( config.EnableVSync ) );

        if ( DxLib_Init() == FAIL ) {
            throw exception::InitializeError( "DxLibの初期化に失敗しました。" );
        }

        SetDrawScreen( DX_SCREEN_BACK );
    }

    void GameLoop::DxFinalize() {
        DxLib_End();
    }
}  // namespace game

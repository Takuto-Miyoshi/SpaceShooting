#include "GameLoop.h"

#include "../Definition/DxLibSetting.h"
#include "DxLib.h"
#include "SceneManager.h"

namespace shooting {
    void GameLoop::Exec() {
        auto sceneManager = shooting::SceneManager();
        sceneManager.Initialize();

        while ( true ) {
            if ( ProcessMessage() == dxlib::FAIL ) { break; }

            ClearDrawScreen();
            clsDx();

            sceneManager.Update();
            if ( sceneManager.EndGame ) { break; }

            ScreenFlip();
        }
    }
}  // namespace shooting

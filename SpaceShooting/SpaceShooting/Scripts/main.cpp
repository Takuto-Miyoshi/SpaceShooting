#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <cstdint>

#include "Definition/DxLibSetting.h"
#include "DxLib.h"
#include "Manager/GameLoop.h"

#define new ::new ( _NORMAL_BLOCK, __FILE__, __LINE__ )

using namespace shooting::dxlib;

auto WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int32_t nShowCmd ) -> int32_t {
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );

    // ------------ DxLib初期設定 -------------
    SetOutApplicationLogValidFlag( FALSE );
    ChangeWindowMode( TRUE );
    SetGraphMode( SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT_DEPTH );
    SetMainWindowText( WINDOW_NAME.c_str() );
    SetWaitVSyncFlag( TRUE );
    if ( DxLib_Init() == FAIL ) { return 0; }
    SetDrawScreen( DX_SCREEN_BACK );
    // ---------------------------------------

    shooting::GameLoop().Exec();

    DxLib_End();
    return 0;
}

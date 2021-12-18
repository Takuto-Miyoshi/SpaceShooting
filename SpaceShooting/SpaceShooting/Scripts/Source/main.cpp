
#define _CRTDBG_MAP_ALLOC
#include <DxLib.h>
#include <crtdbg.h>

#include <Game/GameLoop.hpp>
#include <cstdint>

#define new ::new ( _NORMAL_BLOCK, __FILE__, __LINE__ )

auto WINAPI WinMain( [[maybe_unused]] _In_ HINSTANCE hInstance,
                     [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance,
                     [[maybe_unused]] _In_ LPSTR lpCmdLine,
                     [[maybe_unused]] _In_ int32_t nShowCmd ) -> int32_t {
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );

    auto gameLoop { game::GameLoop( game::GameLoop::DxLibConfig {
        //.ScreenSize { 1920, 1080 },
        .ScreenSize { 1600, 900 },
        .ColorBitDepth { 32 },
        .FrameRate { 60 },
        .EnableFullscreen { false },
        .WindowName { "Shooting" },
        .EnableVSync { false } } ) };

    gameLoop.Exec();

    return 0;
}

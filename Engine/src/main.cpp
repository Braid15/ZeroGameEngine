
#include "ZeroEngine.h"

#include "../test/TestApp.h"

#ifdef _DEBUG
#pragma comment(lib, "vld.lib")
#include "3rdParty\VisualLeakDetector\vld.h"
#endif

#define _SDL_FRAMEWORK

#ifdef _SDL_FRAMEWORK
#pragma comment(lib, "SdlFramework_debug.lib")
#include "../../SdlFramework/SdlFramework.h"
#endif

using namespace ZeroEngine;
using namespace ZeroSdlFramework;

static void run_game() {
    // @TODO: Load options from file.
    GameOptions options;

    // Launcher takes care of deleting these pointers
    GameApp* game = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);
    AFramework* framework = zero_new SdlFramework();

    GameLauncher* launcher = zero_new GameLauncher(game, framework);
    launcher->launch();

    zero_delete(launcher);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    run_game();
    system("PAUSE");
    return 0;
}

/*
int main(int argc, char* args[]) {

    // #ifdef _DEBUG
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // #endif


    run_game();
    // MathTypes::run_all_unit_tests();

    system("PAUSE");

    // #ifdef _DEBUG
    // _CrtDumpMemoryLeaks();
    // #endif

    return 0;
}
*/



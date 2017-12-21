#include "ZeroEngine.h"

#include "../test/TestApp.h"

using namespace ZeroEngine;

static void run_game();

void xml_test() {

    /*
    TiXmlDocument doc("S:/projects/Game-Engines/ZeroGameEngine/Engine/test/test.xml");
    doc.LoadFile();
    TiXmlElement* root = doc.FirstChildElement();
    const char* type = root->Attribute("type");
    const char* resource = root->Attribute("resource");

    TiXmlElement* node = root->FirstChildElement();
    std::cout << node->Value() << "\n";
    node = node->FirstChildElement();
    std::cout << node->Value() << "\n";
    */

    XmlReader reader("S:/projects/Game-Engines/ZeroGameEngine/Engine/test/test.xml");
    reader.load();
    Logger::shutdown();


}

int main( int argc, char* args[] ) {

    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    xml_test();
    // run_game();

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    system("PAUSE");

    return 0;
}

void run_game() {
    // @TODO: Load options from file.
    GameOptions options;

    // Launcher takes care of deleting these pointers
    GameApp* game = zero_new ZeroEngineAppTest::MockZeroEngineApp(options);
    AFramework* framework = zero_new SdlFramework();

    GameLauncher* launcher = zero_new GameLauncher(game, framework);
    launcher->launch();

    zero_delete(launcher);
}

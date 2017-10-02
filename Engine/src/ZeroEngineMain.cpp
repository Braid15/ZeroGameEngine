#include "ZeroEngine.h"


using namespace ZeroEngine;

// SDL requires this main signature
int main ( int argc, char* args[] ) {

    #ifdef _DEBUG
    int debug_flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    debug_flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( debug_flag );
    #endif

    
    if ( Framework::instance()->initialize() ) {
        std::cout << "Framework initialized to " << Framework::instance()->get_framework_factory()->get_id() << std::endl;
    } else {
        std::cout << "Error initializing framework" << std::endl;
    }

    std::cout << Framework::instance()->get_framework_factory()->get_type() << std::endl;
    ILogger* logger = new BaseLogger();


    RectUnitTest::run();




    Framework::instance()->shutdown();

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    return 0;
}
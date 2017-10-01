#include "ZeroEngine.h"


using namespace ZeroEngine;

// SDL requires this main signature
int main ( int argc, char* args[] ) {

    #ifdef _DEBUG
    int debug_flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    debug_flag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( debug_flag );
    #endif

    
    if ( Framework::Instance()->Initialize() ) {
        std::cout << "Framework initialized to " << Framework::Instance()->GetFrameworkFactory()->GetID() << std::endl;
    } else {
        std::cout << "Error initializing framework" << std::endl;
    }

    BaseLogger::_UNIT_TEST_();

    Framework::Instance()->Shutdown();

    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif

    return 0;
}

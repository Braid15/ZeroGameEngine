#include <iostream>
#include <windows.h>
#include "ZeroEngine.h";

using namespace ZeroEngine;

// SDL requires this main signature
int main ( int argc, char* args[] ) {

    IFrameworkFactory::SetFramework( new SDLFrameworkFactory() );
    IFrameworkFactory::Instance()->Cleanup();

    return 0;
}

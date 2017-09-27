#include <iostream>
#include <windows.h>
#include "Framework.h"



int main () {

    const char* framework = ZeroEngine::Framework::IFrameworkFactory::Instance()->GetName();
    MessageBox( NULL, TEXT( framework ), TEXT( "test" ), 0 );
    return 0;
}


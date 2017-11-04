#pragma once

// ------------------------------------------------
// This file will include all standard header files 
// ------------------------------------------------

#define _UNICODE


// Framework is SDL so this isn't really ever needed
#ifdef _WIN_OS
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #include <windowsx.h>
#endif

// If using crtdbg.h, stdlib.h must be included before crtdbg.h
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
    #define zero_new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
    #include <stdlib.h>
    #define zero_new new
#endif

#define zero_delete(x) if(x) delete x; x = nullptr;




#include <tchar.h>
#include <malloc.h> 
#include <memory.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <math.h>
#include <list>
#include <filesystem>
#include <type_traits>
#include <iomanip>
#include <cassert>

#include "IZeroObject.h"

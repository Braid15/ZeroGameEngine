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
    #define zero_malloc(x) _malloc_dbg((x), _NORMAL_BLOCK, __FILE__, __LINE__);
    #define zero_free(x) _free_dbg((x), _NORMAL_BLOCK);
    #define zero_strdup(x) strdup((x))
#else
    #include <stdlib.h>
    #define zero_new new
    #define zero_malloc(x) malloc((x))
    #define zero_free(x) free((x))
    #define zero_strdup(x) strdup((x))
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
#include <array>
#include <vector>
#include <math.h>
#include <list>
#include <filesystem>
#include <typeinfo>
#include <type_traits>
#include <iomanip>
#include <cassert>
#include <strstream>

#include "IZeroObject.h"


// @TEMP - Thrown together quickly.
// Make msg std::string so that const char* or std::string can be passed
#define LOG_DEBUG(agent, msg) \
    printf("[%s::%s] %s\n", agent, __func__, std::string(msg).c_str()); 
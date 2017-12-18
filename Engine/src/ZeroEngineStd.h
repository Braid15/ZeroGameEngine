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


#include "Memory/Memory.h"


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
#include "Logger/Logging.h"


#pragma once


// If using crtdb.h, stdlib.h must be include before crtdbg.h
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
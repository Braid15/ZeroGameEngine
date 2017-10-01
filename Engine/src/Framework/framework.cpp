#include "Framework.h"

// @@TEMPORARY - 9/27/17
#define _SDL_FRAMEWORK_

namespace ZeroEngine {

    Framework* Framework::_instance = nullptr;

    Framework::Framework() {
        _framework_factory = nullptr;
    }

    Framework::~Framework() {
        delete _framework_factory;
        _framework_factory = nullptr;
    }

    // Because this is a singleton and it has an 
    // initialization method, it is necessary that the
    // initialization method is the first method used with this class
    Framework* Framework::instance() {
        if ( !_instance ) {
            _instance = new Framework();
        }
        return _instance;
    }

    bool Framework::initialize() {
        bool success = true;

        //@@TODO: 9/27/2017
        // Need to make it so that the framework
        // is loaded from file instead of using macros
        #ifdef _SDL_FRAMEWORK_
        _framework_factory = new SDLFrameworkFactory();
        #else
        _framework_factory = new NullFrameworkFactory();
        #endif

        success = _framework_factory->initialize();
        return success;
    }

    bool Framework::shutdown() {
        bool success = true;
        success = _framework_factory->shutdown();
        return success;
    }

    IFrameworkFactory* Framework::get_framework_factory() {
        return _framework_factory;
    }
            
            
    
}
#pragma once

#include "../ZeroEngineStd.h"
#include "IFrameworkFactory.h"
#include "NullFrameworkFactory.h"
#include "SDL/SDLFrameworkFactory.h"

namespace ZeroEngine {

    // Facade for all framework stuff.
    // This is a singleton which will give the entire
    // system access to creating framework dependent objects
    // such as windows, renderers, etc.

    class Framework {

    public:
        ~Framework();
        bool Initialize();
        bool Shutdown();
        static Framework* Instance();
        IFrameworkFactory* GetFrameworkFactory();

    private:
        Framework();
        static Framework* _instance;
        // @@TODO: 9/27/17
        // IFrameworkFactory was originally
        // supposed to be a facade, but Framework took it's place.
        // I Eventually want to have seperate instance members for each subsystem,
        // but I will just use IFrameworkFactory until I am set on a design
        IFrameworkFactory* _framework_factory;
    };
}
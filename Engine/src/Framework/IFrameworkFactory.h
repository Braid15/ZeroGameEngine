#pragma once

#include <map>

namespace ZeroEngine { namespace Framework {

    // Interface for all framework factories.
    // Framework factories are facades for the entire framework.
    // A framework will have a reference to the rendering subsystem,
    // audiosubsystem, etc

    class IFrameworkFactory {

        typedef const char* FrameworkName;

    public:
        static IFrameworkFactory* Instance();
        static void SetFramework( FrameworkName name );
        FrameworkName GetName();

    protected:
        IFrameworkFactory();
        IFrameworkFactory( FrameworkName name );
        void Cleanup();
        void SetName( FrameworkName name );

    private:
        FrameworkName _name;
        static FrameworkName _current_framework;
        static IFrameworkFactory* _instance;
    };

} }

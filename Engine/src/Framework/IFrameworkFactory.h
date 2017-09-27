#pragma once
#include <iostream>
#include <map>

namespace ZeroEngine {

    // Interface for all framework factories.
    // Framework factories are facades for the entire framework.
    // A framework will have a reference to the rendering subsystem,
    // audiosubsystem, etc

    class IFrameworkFactory {

        typedef const char* FrameworkName;

    public:
        static IFrameworkFactory* Instance();
        static void SetFramework( IFrameworkFactory* framework_factory );
        virtual void Cleanup();
        FrameworkName GetName();

    protected:
        IFrameworkFactory();
        virtual ~IFrameworkFactory() { std::cout <<"deleting base" << std::endl; };
        IFrameworkFactory( FrameworkName name );
        void SetName( FrameworkName name );

    private:
        FrameworkName _name;
        static FrameworkName _current_framework;
        static IFrameworkFactory* _instance;
    };

}

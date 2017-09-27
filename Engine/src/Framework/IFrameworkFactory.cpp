#include "IFrameworkFactory.h"
//TODO: Get rid of this include
#include "NullFrameworkFactory.h"

namespace ZeroEngine {

    IFrameworkFactory* IFrameworkFactory::_instance = nullptr;

    IFrameworkFactory::IFrameworkFactory() {
        _name = "NO NAME";
    }

    IFrameworkFactory::IFrameworkFactory( IFrameworkFactory::FrameworkName name ) {
        _name = name;
    }

    IFrameworkFactory* IFrameworkFactory::Instance () {
        if ( _instance == nullptr ) {
            _instance = new NullFrameworkFactory();
        }
        return _instance;
    }

    IFrameworkFactory::FrameworkName IFrameworkFactory::GetName() {
        return _name;
    }

    void IFrameworkFactory::SetName( IFrameworkFactory::FrameworkName name ) {
        _name = name;
    }

    void IFrameworkFactory::SetFramework( IFrameworkFactory* framework_factory ) {
        _instance = framework_factory;
    }

    void IFrameworkFactory::Cleanup() {
        delete _instance;
        _instance = nullptr;
    }

}

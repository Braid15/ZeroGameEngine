#include "IFrameworkFactory.h"
#include "NullFrameworkFactory.h"

using ZeroEngine::Framework::IFrameworkFactory;

IFrameworkFactory::FrameworkName IFrameworkFactory::_current_framework = "NO FRAMEWORK";
IFrameworkFactory* IFrameworkFactory::_instance = nullptr;

IFrameworkFactory::IFrameworkFactory() {
    _name = "NO NAME";
}

IFrameworkFactory::IFrameworkFactory( IFrameworkFactory::FrameworkName name ) {
    _name = name;
}

IFrameworkFactory* IFrameworkFactory::Instance () {
    if ( _instance == nullptr ) {
        if ( strcmp( _current_framework, "SDL_FRAMEWORK" ) == 0 ) {
            _instance = nullptr;
        } else {
            _instance = new NullFrameworkFactory();
        }
    }
    return _instance;
}

IFrameworkFactory::FrameworkName IFrameworkFactory::GetName() {
    return _name;
}

void IFrameworkFactory::SetName( IFrameworkFactory::FrameworkName name ) {
    _name = name;
}

void IFrameworkFactory::SetFramework( IFrameworkFactory::FrameworkName name ) {
    _current_framework = name;
}

void IFrameworkFactory::Cleanup() {
    delete _instance;
    _instance = nullptr;
}


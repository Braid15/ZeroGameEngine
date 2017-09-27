#include "NullFrameworkFactory.h"

using ZeroEngine::NullFrameworkFactory;

NullFrameworkFactory::NullFrameworkFactory() : IFrameworkFactory::IFrameworkFactory( "Null_Framework_Factory" ) {}

NullFrameworkFactory::~NullFrameworkFactory() {
    IFrameworkFactory::Cleanup();
}

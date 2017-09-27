#include "NullFrameworkFactory.h"

using ZeroEngine::Framework::IFrameworkFactory;
using ZeroEngine::Framework::NullFrameworkFactory;

NullFrameworkFactory::NullFrameworkFactory() : IFrameworkFactory::IFrameworkFactory( "Null_Framework_Factory" ) {}

NullFrameworkFactory::~NullFrameworkFactory() {
    IFrameworkFactory::Cleanup();
}

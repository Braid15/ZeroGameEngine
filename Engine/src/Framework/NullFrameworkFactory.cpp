#include "NullFrameworkFactory.h"

namespace ZeroEngine {

    NullFrameworkFactory::NullFrameworkFactory() : BaseFrameworkFactory( "Null Factory" ) {}

    NullFrameworkFactory::~NullFrameworkFactory() {}

    bool NullFrameworkFactory::Initialize() {
        return true;
    }

    bool NullFrameworkFactory::Shutdown() {
        return true;
    }
}



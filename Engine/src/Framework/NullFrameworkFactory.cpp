#include "NullFrameworkFactory.h"

namespace ZeroEngine {

    NullFrameworkFactory::NullFrameworkFactory() : BaseFrameworkFactory( "Null Factory" ) {}

    NullFrameworkFactory::~NullFrameworkFactory() {}

    bool NullFrameworkFactory::initialize() {
        return true;
    }

    bool NullFrameworkFactory::shutdown() {
        return true;
    }
}



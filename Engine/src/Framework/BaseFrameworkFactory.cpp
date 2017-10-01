#include "BaseFrameworkFactory.h"

namespace ZeroEngine {

    BaseFrameworkFactory::BaseFrameworkFactory( FrameworkFactoryID id ) {
        _id = id;
    }

    BaseFrameworkFactory::~BaseFrameworkFactory() {
        _id = nullptr;
    }

    FrameworkFactoryID BaseFrameworkFactory::get_id() {
        return _id;
    }
}
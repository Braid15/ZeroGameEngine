#include "SDLFrameworkFactory.h"

namespace ZeroEngine {

    SDLFrameworkFactory::SDLFrameworkFactory() : BaseFrameworkFactory( "SDL" ) {}

    SDLFrameworkFactory::~SDLFrameworkFactory() {}

    bool SDLFrameworkFactory::initialize() {
        bool success = true;
        return success;
    }

    bool SDLFrameworkFactory::shutdown() {
        bool success = true;
        return success;
    }

}
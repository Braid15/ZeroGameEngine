#include "SDLFrameworkFactory.h"

namespace ZeroEngine {

    SDLFrameworkFactory::SDLFrameworkFactory() : BaseFrameworkFactory( "SDL" ) {}

    SDLFrameworkFactory::~SDLFrameworkFactory() {}

    bool SDLFrameworkFactory::Initialize() {
        bool success = true;
        return success;
    }

    bool SDLFrameworkFactory::Shutdown() {
        bool success = true;
        return success;
    }

}
#include "SDLFrameworkFactory.h"
#include <iostream>

namespace ZeroEngine {

    SDLFrameworkFactory::SDLFrameworkFactory() : IFrameworkFactory( "SDL_Framework_Factory" ) {}

    SDLFrameworkFactory::~SDLFrameworkFactory() { std::cout << "deleting derived" << std::endl; }
}
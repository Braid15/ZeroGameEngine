#include "../../3rdParty/SDL/SDL.h";
#include "../IFrameworkFactory.h";

namespace ZeroEngine {

    class SDLFrameworkFactory : public IFrameworkFactory {

    public:
        SDLFrameworkFactory();
        ~SDLFrameworkFactory();
    };
}


#include <iostream>
#include <windows.h>
#include "Framework.h"
#include "../3rdParty/SDL/sdl.h"


SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Surface* surface2 = nullptr;

bool init() {

    bool success = true;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "SDL could not initialize." << SDL_GetError() << std::endl;
        success = false; 
    } else {
        window = SDL_CreateWindow( "TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN );
        if ( !window ) {
            std::cout << "Error creating window." << SDL_GetError() << std::endl;
            success = false;
        } else {
            surface = SDL_GetWindowSurface( window );
        }
    }

    return success;
}

bool load_media() {

    bool success = true;

    surface2 = SDL_LoadBMP( "assets/test.bmp" );
    if ( !surface2 ) {
        std::cout << "Error creating surface texture" << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void close() {

    SDL_FreeSurface( surface2 );
    surface = nullptr;
    SDL_DestroyWindow( window );
    window = nullptr;
    SDL_Quit();
}

// SDL requires this main signature
int main ( int argc, char* args[] ) {

//    const char* framework = ZeroEngine::Framework::IFrameworkFactory::Instance()->GetName();

    if ( !init() ) {
        std::cout << "Error initializing SDL" << std::endl;
    } else {
        if ( !load_media() ) {
            std::cout << "Error loading media" << std::endl;
        } else {

            SDL_BlitSurface( surface2, NULL, surface, NULL );
            SDL_UpdateWindowSurface( window );
        }
    }

    SDL_Delay( 6000 );
    close();

    return 0;
}


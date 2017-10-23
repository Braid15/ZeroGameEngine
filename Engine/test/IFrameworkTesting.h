#ifdef _DEBUG

#include "../src/ZeroEngine.h"
#include "../src/3rdParty/SDL/SDL.h"

using namespace ZeroEngine;

namespace IFrameworkTesting {

    class MockFramework : public AFramework {
    public:
        inline MockFramework() {}

    /* IFramework */
    public:
        inline IRenderer* create_renderer() { return nullptr; }
        inline IWindow* create_window() { return nullptr; }
        bool initialize();
        bool shutdown();
        bool get_app_msg() override;
        void frame_begin( Time delta_time ) override;
        void frame_render( Time delta_time ) override;
        inline StringRepr to_string() const { return "MockFramework"; }

    private:
        SDL_Window* _window = nullptr;
        SDL_Surface* _surface = nullptr;
    };

}

#endif
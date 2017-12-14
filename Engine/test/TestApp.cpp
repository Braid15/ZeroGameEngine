#ifdef _DEBUG

#include "TestApp.h"

namespace ZeroEngineAppTest {

    BaseGameLogic* MockZeroEngineApp::create_game_and_view() {
        BaseGameLogic* logic = zero_new TestGameLogic();
        logic->initialize();
        IGameViewPtr view(zero_new TestGameView(IRenderer::ptr(zero_new NullRenderer())));
        logic->add_game_view(view);
        return logic;
    }
}

#endif
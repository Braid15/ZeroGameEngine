#ifdef _DEBUG

#pragma once

#include "../src/ZeroEngine.h"

using namespace ZeroEngine;

namespace ZeroEngineAppTest {

    class TestGameLogic;
    class TestGameView;

    class MockZeroEngineApp : public ZeroEngineApp {

    public:
        MockZeroEngineApp(GameOptions& options) : ZeroEngineApp(options) {}
        inline ~MockZeroEngineApp() {}
        const std::string get_game_title() override { return "Test App"; }
        const std::string get_game_app_directory() override { return "idk"; }
    protected:
        BaseGameLogic* create_game_and_view() override;

    };

    class TestGameLogic : public BaseGameLogic {
    public:
        inline StringRepr to_string() const override { return "TestGameLogic"; }

    };


    class TestGameView : public HumanView {
    public:
        explicit TestGameView(IRenderer::ptr renderer) : HumanView(renderer) {}
        inline StringRepr to_string() const override { return "TestGameView"; }
    };

}

#endif

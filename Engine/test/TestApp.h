#ifdef _DEBUG

#pragma once

#include "../src/ZeroEngine.h"

using namespace ZeroEngine;

namespace ZeroEngineAppTest {

    class MockZeroEngineApp : public ZeroEngineApp {

    public:
        MockZeroEngineApp(GameOptions& options) : ZeroEngineApp(options) {}
        ~MockZeroEngineApp();
        const std::string get_game_title() override { return "Test App"; }
        const std::string get_game_app_directory() override { return "idk"; }
        bool load_game() override { return true; }
        bool on_msg_proc(const AppMsg* const msg) override;
        void on_update(Ticks time) override;

    // TESTING
    public:
        void entity_created_delegate(IEventDataPtr event_data);

    protected:
        void register_game_events() override;
    };
}

#endif

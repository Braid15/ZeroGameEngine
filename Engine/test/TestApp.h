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
    protected:
        inline void on_register_event_delegates() override;
        inline void on_unregister_event_delegates() override;

    };

    inline void TestGameLogic::on_register_event_delegates() {
        ZeroEventManager::register_listener(
            fastdelegate::MakeDelegate(this, &TestGameLogic::attach_process_event_delegate),
            AttachProcessEvent::type);
    }

    inline void TestGameLogic::on_unregister_event_delegates() {
        ZeroEventManager::unregister_listener(
            fastdelegate::MakeDelegate(this, &TestGameLogic::attach_process_event_delegate),
            AttachProcessEvent::type);
    }


    class TestGameView : public HumanView {
    public:
        explicit TestGameView(IRenderer::ptr renderer) : HumanView(renderer) {}
        inline StringRepr to_string() const override { return "TestGameView"; }
    protected:
        inline bool on_msg_proc(AppMsg::ptr msg, bool handled) override;
    };

    inline bool TestGameView::on_msg_proc(AppMsg::ptr msg, bool handled) {
        /*
        if (msg->is_type(KeyboardMsg::type)) {
            KeyboardMsg::ptr key = KeyboardMsg::cast(msg);
            if (key->is_key_press(Keys::enter)) {
                ZeroEventManager::queue_event(AttachProcessEvent::create(TimedProcess::ptr(zero_new TimedProcess(4000))));
                return true;
            }
        }
        */
        return false;
    }
}

#endif

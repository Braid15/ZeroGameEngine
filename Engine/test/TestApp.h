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


    class TestMovementController : public IMouseHandler, public IKeyboardHandler {
    public:
        inline TestMovementController() {}
        inline ~TestMovementController() {}

        inline bool on_key_down(const Key& key) override {
            std::cout << "on_key_down() - " << key << "\n";
            return false;
        }

        inline bool on_key_up(const Key& key) override {
            std::cout << "on_key_up() - " << key << "\n";
            return false;
        }

        inline bool on_mouse_move(const Point<int32_t> pos, const int radius) override {
            std::cout << "on_mouse_move() - " << pos << "\n";
            return false;
        }

        inline bool on_button_down(const Point<int32_t> pos, const int radius, const MouseButton& button) override {
            std::cout << "on_button_down() - " << pos << " " << button << "\n";
            return false;
        }

        inline bool on_button_up(const Point<int32_t> pos, const int radius, const MouseButton& button) override {
            std::cout << "on_button_up() - " << pos << " " << button << "\n";
            return false;
        }
    };

    class TestGameView : public HumanView {
        std::shared_ptr<TestMovementController> _controller;
    public:
        explicit TestGameView(IRenderer::ptr renderer) : HumanView(renderer) {}
        inline StringRepr to_string() const override { return "TestGameView"; }
    protected:

        inline bool on_load_game() override {
            _controller = std::shared_ptr<TestMovementController>(zero_new TestMovementController());
            set_keyboard_handler(_controller);
            set_mouse_handler(_controller);
            return true;
        }

        inline bool on_msg_proc(AppMsg::ptr msg, bool handled) override {
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
    };


}

#endif

#ifdef _DEBUG

#pragma once

#include "../src/ZeroEngine.h"

using namespace ZeroEngine;

namespace ZeroEngineAppTest {

    class TestGameLogic;
    class TestGameView;

    class MockZeroEngineApp : public GameApp {
    public:
        MockZeroEngineApp(GameOptions& options) : GameApp(options) {}
        inline ~MockZeroEngineApp() {}
        const std::string get_game_title() override { return "Test App"; }
        const std::string get_game_app_directory() override { return "idk"; }
    protected:
        BaseGameLogic* create_game_and_view() override;
    };



    class Pen {
    private:
        Color _color;
        bool _drawing;
        Point<int32_t> _start;
        Point<int32_t> _end;

    public:
        Pen() : _color(Colors::white()), _drawing(false) {}
        void set_color(Color color) { _color = color; }

        void draw_start(Point<int32_t> start) {
            _start = start;
        }

        void draw_end(Point<int32_t> end) {
            _end = end;
            ZeroEventManager::queue_event(DrawLineEvent::create(_start, _end, _color));
        }
    };

    class TestGameLogic : public BaseGameLogic {
    public:
        inline StringRepr to_string() const override { return "TestGameLogic"; }
    protected:
        inline void TestGameLogic::on_register_event_delegates() {
            ZeroEventManager::register_listener(
                fastdelegate::MakeDelegate(this, &TestGameLogic::attach_process_event_delegate),
                AttachProcessEvent::type);

            ZeroEventManager::register_listener(
                fastdelegate::MakeDelegate(this, &TestGameLogic::draw_line_event),
                DrawLineEvent::type);
        }

        inline void TestGameLogic::on_unregister_event_delegates() {
            ZeroEventManager::unregister_listener(
                fastdelegate::MakeDelegate(this, &TestGameLogic::attach_process_event_delegate),
                AttachProcessEvent::type);

            ZeroEventManager::unregister_listener(
                fastdelegate::MakeDelegate(this, &TestGameLogic::draw_line_event),
                DrawLineEvent::type);
        }

        inline void draw_line_event(IEventDataPtr event_data) {
            DrawLineEvent::ptr data = DrawLineEvent::cast(event_data);
            GameApp::instance()->get_human_view()->add_screen_element(IScreenElement::ptr(zero_new LineScreenElement(
                    data->get_from_point(), data->get_to_point(), data->get_color())));
        }
    };

    class TestMovementController : public IMouseHandler, public IKeyboardHandler {
    private:
        Pen pen;
    public:
        inline TestMovementController() {}
        inline ~TestMovementController() {}

        inline bool on_key_down(const Key& key) override {
            if (key == Key::enter) {
                pen.set_color(Colors::blue());
            } else if (key == Key::space) {
                pen.set_color(Colors::green());
            }
            return true;
        }

        inline bool on_key_up(const Key& key) override {
            return false;
        }

        inline bool on_mouse_move(const Point<int32_t> pos, const int radius) override {
            return false;
        }

        inline bool on_button_down(const Point<int32_t> pos, const int radius, const MouseButton& button) override {
            // In actuality there should be draw start and draw end events which will be handled by the game logic
            if (button == MouseButton::left) {
                pen.draw_start(pos);
            }
            return true;
        }

        inline bool on_button_up(const Point<int32_t> pos, const int radius, const MouseButton& button) override {
            if (button == MouseButton::left) {
                pen.draw_end(pos);
            }
            return true;
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
    };
}

#endif

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

    class Pen {
    private:
        Color _color;
        bool _drawing;
        Point<int32_t> _start;
        Point<int32_t> _end;

        std::list<LineRenderPacket::s_ptr> _lines;

    public:
        Pen() : _color(Colors::white()), _drawing(false) {}
        void set_color(Color color) { _color = color; }

        void draw_start(Point<int32_t> start) {
            _start = start;
        }

        void draw_end(Point<int32_t> end) {
            _end = end;

            // @TODO: I want this to provide a different interface than the IRenderer interface
            // so that client code doesn't have access to methods such as initialize() or shutdown(), etc
            LineRenderPacket::s_ptr line(zero_new LineRenderPacket(_start, _end, _color));
            _lines.push_back(line);
            Game::get_renderer()->submit_packet(line);
            // ZeroEventManager::queue_event(DrawLineEvent::create(_start, _end, _color));
        }

        void remove_last_line() {
            uint32_t size = static_cast<uint32_t>(_lines.size());
            if (size > 0) {
                LineRenderPacket::s_ptr line = _lines.back();
                _lines.pop_back();
                Game::get_renderer()->remove_packet(line);
            }

            LOG_DEBUG("Pen", std::to_string(size));
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
                // ZeroEventManager::queue_event(RequestCreateEntityEvent::create());
            } else if (key == Key::space) {
                // ZeroEventManager::queue_event(RequestDestroyEntityEvent::create(Game::get_entity_count()));
            } else if (key == Key::backspace) {
                pen.remove_last_line();
            } else if (Key_is_numeric(key)) {
                std::cout << Key_get_numeric_value(key) << "\n";
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
    private:
        friend class TestMovementController;
        std::shared_ptr<TestMovementController> _controller;
    public:
        explicit TestGameView(IRenderer::s_ptr renderer) : HumanView(renderer) {}
        inline StringRepr to_string() const override { return "TestGameView"; }
    protected:
        inline bool on_load_game() override {
            _controller = std::shared_ptr<TestMovementController>(zero_new TestMovementController());
            set_keyboard_handler(_controller);
            set_mouse_handler(_controller);
            return true;
        }

        inline void entity_created_event_delegate(IEventDataPtr event_data) {
            EntityCreatedEvent::ptr data = EntityCreatedEvent::cast(event_data);
            std::cout << "Entity created: " << data->get_entity_id() << "\n";
            std::cout << "ENtity count: " << Game::get_entity_count() << "\n";
        }

        inline void entity_destroyed_event_delegate(IEventDataPtr event_data) {
            EntityDestroyedEvent::ptr data = EntityDestroyedEvent::cast(event_data);
            std::cout << "Entity destroyed: " << data->get_entity_id() << "\n";
            std::cout << "ENtity count: " << Game::get_entity_count() << "\n";
        }

        inline void on_register_event_delegates() override {
            LOG_DEBUG("TestGameView", "Called");
            ZeroEventManager::register_listener(
                fastdelegate::MakeDelegate(this, &TestGameView::entity_destroyed_event_delegate),
                EntityDestroyedEvent::type);

            ZeroEventManager::register_listener(
                fastdelegate::MakeDelegate(this, &TestGameView::entity_created_event_delegate),
                EntityCreatedEvent::type);
        }

        inline void on_unregister_event_delegates() override {
            ZeroEventManager::unregister_listener(
                fastdelegate::MakeDelegate(this, &TestGameView::entity_destroyed_event_delegate),
                EntityDestroyedEvent::type);

            ZeroEventManager::unregister_listener(
                fastdelegate::MakeDelegate(this, &TestGameView::entity_created_event_delegate),
                EntityCreatedEvent::type);
        }
    };
}

#endif

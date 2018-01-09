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
        }

        inline void TestGameLogic::on_unregister_event_delegates() {
            ZeroEventManager::unregister_listener(
                fastdelegate::MakeDelegate(this, &TestGameLogic::attach_process_event_delegate),
                AttachProcessEvent::type);

        }
    };

    class Pen {
    private:
        Color _color;
        bool _drawing;
        Point<Int32> _start;
        Point<Int32> _end;

        Uint32 _blue = 0x0000FFFF;
        Uint32 _red = 0xFF0000FF;
        Uint32 _green = 0x00FF00FF;

        Uint32 _colors[3] = {_blue, _red, _green };

        Uint32 _cur_index;

        std::list<LineRenderPacket::s_ptr> _lines;

    public:
        Pen() : _color(Colors::white()), _drawing(false), _cur_index(0) {}

        void set_color(Color color) { _color = color; }

        void change_line_colors() {
            _color.set(_colors[_cur_index++]);

            if (_cur_index >= 3) {
                _cur_index = 0;
            }

            for (auto line : _lines) {
                line->set_color(_color);
            }
        }

        void draw_start(Point<Int32> start) {
            _start = start;
        }

        void draw_end(Point<Int32> end) {
            _end = end;

            // @TODO: I want this to provide a different interface than the IRenderer interface
            // so that client code doesn't have access to methods such as initialize() or shutdown(), etc
            LineRenderPacket::s_ptr line(zero_new LineRenderPacket(_start, _end, _color));
            _lines.push_back(line);
            Game::get_renderer()->submit_packet(line);
            // ZeroEventManager::queue_event(DrawLineEvent::create(_start, _end, _color));
        }

        void remove_last_line() {
            Uint32 size = static_cast<Uint32>(_lines.size());
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
        friend class TestGameView;
        Pen pen;
        std::vector<EntityId> _entity_id_list;
        Vector2 _left;
        Vector2 _right;
        Vector2 _up;
        Vector2 _down;
        Vector3 _vertices[4];
        Vector2 _verts[4];

        std::shared_ptr<VertexRenderPacket> _render_packet;
        Rect _rect;

        bool _go_up;
        bool _go_down;
        bool _go_right;
        bool _go_left;




    public:
        inline TestMovementController() 
            : _left(-1, 0), _right(1, 0), _down(0, 1), _up(0, -1)
             , _go_up(false), _go_down(false), _go_right(false), _go_left(false) {

            _vertices[0] = Vector3(Game::get_screen_width() / 2, Game::get_screen_height() / 2, 1);
            _vertices[1] = Vector3(_vertices[0].get_x() + 100, _vertices[0].get_y(), 1.0f);
            _vertices[2] = Vector3(_vertices[1].get_x(), _vertices[1].get_y() + 100, 1.0f);
            _vertices[3] = Vector3(_vertices[2].get_x() - 100, _vertices[2].get_y(), 1.0f);

            //_rect.set(_vertices[0][0], _vertices[0][1], _vertices[1][0], _vertices[2][1]);
            _verts[0] = Vector2(_vertices[0]);
            _verts[1] = Vector2(_vertices[1]);
            _verts[2] = Vector2(_vertices[2]);
            _verts[3] = Vector2(_vertices[3]);


            _render_packet = std::make_shared<VertexRenderPacket>(_verts, 4, Colors::white());
        }
        inline ~TestMovementController() {}

        inline void send_rect_packet() {
            //Game::get_renderer()->remove_packet(_render_packet);
            //_rect.set(_vertices[0][0], _vertices[0][1], _vertices[1][0], _vertices[2][1]);
            _verts[0] = Vector2(_vertices[0]);
            _verts[1] = Vector2(_vertices[1]);
            _verts[2] = Vector2(_vertices[2]);
            _verts[3] = Vector2(_vertices[3]);


            _render_packet->set_vertices(_verts, 4);
            //_render_packet->set_rect(_rect);
            //Game::get_renderer()->submit_packet(t);
        }

        inline bool on_key_down(const Key& key) override {
            if (key == Key::enter) {
                Game::get_renderer()->submit_packet(_render_packet);

                /*
                const char* p = "S:\\projects\\game-engines\\zerogameengine\\engine\\test\\test-entity.xml";
                Vector3 pos = Vector3(Game::get_screen_width() / 2, Game::get_screen_height() / 2, 1);
                ZeroEventManager::queue_event(RequestCreateEntityEvent::create(p, pos));
                */
            } else if (key == Key::space) {
                if (!_entity_id_list.empty()) {
                    EntityId id = _entity_id_list.back();
                    _entity_id_list.pop_back();
                    ZeroEventManager::queue_event(RequestDestroyEntityEvent::create(id));
                }
            } else if (key == Key::backspace) {
                pen.remove_last_line();
            } else if (Key_is_numeric(key)) {
                std::cout << Key_get_numeric_value(key) << "\n";
            } else if (key == Key::w) {
                _go_up = true;
            } else if (key == Key::s) {
                _go_down = true;
            } else if (key == Key::a) {
                _go_left = true;
            } else if (key == Key::d) {
                _go_right = true;
            }
            return true;
        }

        inline bool on_key_up(const Key& key) override {
            if (key == Key::w) {
                _go_up = false;
            } else if (key == Key::s) {
                _go_down = false;
            } else if (key == Key::a) {
                _go_left = false;
            } else if (key == Key::d) {
                _go_right = false;
            }
            return true;
        }

        inline bool on_mouse_move(const Point<Int32> pos, const Int32 radius) override {
            return false;
        }

        inline bool on_button_down(const Point<Int32> pos, const Int32 radius, const MouseButton& button) override {
            // In actuality there should be draw start and draw end events which will be handled by the game logic
            if (button == MouseButton::left) {
                pen.draw_start(pos);
            }
            return true;
        }

        inline bool on_button_up(const Point<Int32> pos, const Int32 radius, const MouseButton& button) override {
            if (button == MouseButton::left) {
                pen.draw_end(pos);
            }
            return true;
        }

        inline void update(Tick delta_time) {
            if (_go_up || _go_down || _go_left || _go_right /*&& !_entity_id_list.empty()*/) {
                /*
                auto entity = Game::get_entity(_entity_id_list.back()).lock();
                auto transform = entity->get_component<TransformComponent2D>(TransformComponent2D::id).lock();
                */

                Vector2 direction;

                if (_go_up) direction += _up;
                if (_go_down) direction += _down;
                if (_go_left) direction += _left;
                if (_go_right) direction += _right;

                direction *= delta_time;

                Matrix3x3 mat = Matrix3x3::identity();

                /*
                Vector2 scale_mat(1, 1);
                if (_go_up) {
                    scale_mat.set(1.2);
                } else if (_go_down) {
                    scale_mat.set(0.7);
                }

                Vector2 center = Vector2(static_cast<Float32>(_rect.get_center().get_x()), static_cast<Float32>(_rect.get_center().get_y()));
                // Fixed point scaling
                mat = mat * Matrix3x3::get_translation_2D(center);
                mat = mat * Matrix3x3::get_scaling_2D(scale_mat);
                mat = mat * Matrix3x3::get_translation_2D(-center);
                */

                Float32 degree = 0.0f;

                if (_go_up) {
                    degree = 2;
                } else if (_go_down) {
                    degree = -2;
                }

                //Vector2 center = Vector2(static_cast<Float32>(_rect.get_x()), static_cast<Float32>(_rect.get_y()));
                //mat = mat * Matrix3x3::get_translation_2D(center);
                mat = mat * Matrix3x3::get_rotation_2D(Vector2(_vertices[0].get_x(), _vertices[0].get_y()), degree);
                //mat = mat * Matrix3x3::get_translation_2D(-center);



                //mat = Matrix3x3::get_rotation_2D(transform->get_position(), 90); // * Matrix3x3::get_translation_2D(direction);
                for (auto& vert : _vertices) {
                    vert.transform_by_matrix(mat);
                }

                send_rect_packet();

                //ZeroEventManager::queue_event(MoveEntityEvent::create(entity->get_id(), mat));
            }
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

        DECLARE_EVENT_DELEGATE_SIG(EntityDestroyedEvent, data_ptr) {
        }

        inline bool on_load_game() override {
            _controller = std::shared_ptr<TestMovementController>(zero_new TestMovementController());
            set_keyboard_handler(_controller);
            set_mouse_handler(_controller);
            return true;
        }

        DECLARE_EVENT_DELEGATE_SIG(EntityCreatedEvent, data_ptr) {
            EntityCreatedEvent::s_ptr data = EntityCreatedEvent::cast(data_ptr);
            auto entity = Game::get_entity(data->get_entity_id()).lock();
            _controller->_entity_id_list.push_back(data->get_entity_id());

            std::cout << entity->get_name() << "\n" << entity->create_xml_string() << "\n";
        }

        inline void on_register_event_delegates() override {
            REGISTER_EVENT_DELEGATE(TestGameView, EntityDestroyedEvent);
            REGISTER_EVENT_DELEGATE(TestGameView, EntityCreatedEvent);
        }

        inline void on_unregister_event_delegates() override {
            UNREGISTER_EVENT_DELEGATE(TestGameView, EntityDestroyedEvent);
            UNREGISTER_EVENT_DELEGATE(TestGameView, EntityCreatedEvent);
        }

        inline void update(Tick delta_time) override {
            HumanView::update(delta_time);
            _controller->update(delta_time);
        }
    };
}

#endif

#include "HumanView.h"
#include "../AppLayer/Game.h"

namespace ZeroEngine {

    // @@TEMP
    const unsigned int REFRESH_RATE(1000 / 60);

    const uint32_t INVALID_PLAYER_NUMBER = 0;

    HumanView::HumanView(IRenderer::s_ptr renderer) {
        _renderer = renderer;
        _view_id = INVALID_GAME_VIEW_ID;
        _view_type = GameViewType::human;
        _current_tick = 0;
        _last_draw = 0;
        _is_full_speed = true;
        _is_paused = false;
        _process_manager = zero_new ProcessManager();
        _keyboard_handler = std::shared_ptr<IKeyboardHandler>(zero_new NullKeyboardHandler);
        _mouse_handler = std::shared_ptr<IMouseHandler>(zero_new NullMouseHandler());
        _player_number = INVALID_PLAYER_NUMBER;
        _is_initialized = false;
    }

    HumanView::~HumanView() {
        unregister_event_delegates();
        while (!_screen_elements.empty()) {
            _screen_elements.pop_front();
        }
        zero_delete(_process_manager);
    }

    void HumanView::initialize() {
        if (!_is_initialized) {
            initialize_audio();
            register_event_delegates();
            _is_initialized = true;
        }
    }

    bool HumanView::render(Tick delta_time) {
        bool success = false;
        _current_tick = Game::get_ticks();

        if (!(_current_tick == _last_draw)) {
            if (_is_full_speed || ((_current_tick - _last_draw) > REFRESH_RATE)) {
                if (_renderer->pre_render()) {

                    _screen_elements.sort(IScreenElement::sort_by_z_order_predicate());

                    for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
                        if ((*iter)->is_visible()) {
                            (*iter)->render(delta_time);
                        }
                    }

                    render_text();
                }
            }

            // render console

            _last_draw = _current_tick;
        }
        _renderer->post_render();

        return success;
    }

    bool HumanView::restore() {
        // @TODO: ret does nothing
        bool success = true;
        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->restore();
        }
        return success;
    }

    bool HumanView::lost_device() {
        // @TODO: ret does nothing
        bool success = true;
        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->lost_device();
        }
        return success;
    }

    void HumanView::update(Tick delta_time) {

        _process_manager->update_processes(delta_time);

        // update console

        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->update(delta_time);
        }
    }

    void HumanView::attach(GameViewId view_id, EntityId entity_id) {
        _view_id = view_id;
        _entity_id = entity_id;
    }

    bool HumanView::msg_proc(AppMsg::ptr msg) {
        bool handled = false;

        // It is important to iterate through the screen elements in reverse order
        for (ScreenElementList::reverse_iterator iter = _screen_elements.rbegin(); iter != _screen_elements.rend(); ++iter) {
            if ((*iter)->is_visible()) {
                if ((*iter)->on_msg_proc(msg)) {
                    handled = true;
                    break;
                }
            }
        }

        if (!handled) {
            assert(_keyboard_handler != nullptr);
            assert(_mouse_handler != nullptr);

            if (msg->is_type(KeyboardMsg::type)) {
                KeyboardMsg::ptr keyboard_msg = KeyboardMsg::cast(msg);
                // @NOTE: Sending key press instead of key down for now.
                // Key press does not trigger if it is being held, but just when it is pressed.
                if (keyboard_msg->is_key_press()) {
                    handled = _keyboard_handler->on_key_down(keyboard_msg->get_key());
                } else if (keyboard_msg->is_key_up()) {
                    handled = _keyboard_handler->on_key_up(keyboard_msg->get_key());
                }
            } else if (msg->is_type(MouseButtonMsg::type)) {
                MouseButtonMsg::ptr mouse_button = MouseButtonMsg::cast(msg);
                if (mouse_button->is_button_down()) {
                    handled = _mouse_handler->on_button_down(mouse_button->get_coordinates(), _mouse_radius,
                                                             mouse_button->get_button());
                } else if (mouse_button->is_button_up()) {
                    handled = _mouse_handler->on_button_up(mouse_button->get_coordinates(), _mouse_radius,
                                                           mouse_button->get_button());
                }
            } else if (msg->is_type(MouseMotionMsg::type)) {
                MouseMotionMsg::ptr mouse_motion = MouseMotionMsg::cast(msg);
                handled = _mouse_handler->on_mouse_move(mouse_motion->get_coordinates(), _mouse_radius);
            }
        }

        // on_msg_proc can be overriden by sub classes if they need another way
        // to access the msg
        handled = (on_msg_proc(msg, handled) == true) ? true : handled;

        return handled;
    }

    void HumanView::add_screen_element(IScreenElement::ptr screen_element) {
        _screen_elements.push_back(screen_element);
    }

    void HumanView::remove_screen_element(IScreenElement::ptr screen_element) {
        _screen_elements.remove(screen_element);
    }

    //
    // Private members
    //

    void HumanView::register_event_delegates() {
        on_register_event_delegates();
    }

    void HumanView::unregister_event_delegates() {
        on_unregister_event_delegates();
    }
}
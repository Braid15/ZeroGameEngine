#include "HumanView.h"

namespace ZeroEngine {

    // @@TEMP
    const unsigned int REFRESH_RATE(1000 / 60);

    HumanView::HumanView(IRenderer::ptr renderer) {
        _renderer = renderer;
        _view_id = INVALID_GAME_VIEW_ID;
        _view_type = GameViewType::human;
        _current_tick = 0;
        _last_draw = 0;
        _is_full_speed = true;
        _is_paused = false;
        _process_manager = zero_new ProcessManager();

        // @TODO: Rather this stuff be in an init method
        initialize_audio();
        register_event_delegates();
    }

    HumanView::~HumanView() {
        unregister_event_delegates();
        while (!_screen_elements.empty()) {
            _screen_elements.pop_front();
        }
        zero_delete(_process_manager);
    }

    bool HumanView::on_render(Tick delta_time) {
        bool success = false;
        _current_tick = ZeroFramework::get_ticks();

        if (!(_current_tick == _last_draw)) {
            if (_is_full_speed || ((_current_tick - _last_draw) > REFRESH_RATE)) {
                if (_renderer->pre_render()) {

                    _screen_elements.sort(IScreenElement::sort_by_z_order_predicate());

                    for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
                        if ((*iter)->is_visible()) {
                            (*iter)->on_render(delta_time);
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

    bool HumanView::on_restore() {
        // @TODO: ret does nothing
        bool success = true;
        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->on_restore();
        }
        return success;
    }

    bool HumanView::on_lost_device() {
        // @TODO: ret does nothing
        bool success = true;
        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->on_lost_device();
        }
        return success;
    }

    void HumanView::on_update(Tick delta_time) {

        _process_manager->update_processes(delta_time);

        // update console

        for (auto iter = _screen_elements.begin(); iter != _screen_elements.end(); ++iter) {
            (*iter)->on_update(delta_time);
        }
    }

    void HumanView::on_attach(GameViewId view_id, EntityId entity_id) {
        _view_id = view_id;
        _entity_id = entity_id;
    }

    bool HumanView::on_msg_proc(const AppMsg* const app_msg) {
        bool handled = false;

        // It is important to iterate through the screen elements in reverse order
        for (ScreenElementList::reverse_iterator iter = _screen_elements.rbegin(); iter != _screen_elements.rend(); ++iter) {
            if ((*iter)->is_visible()) {
                if ((*iter)->on_msg_proc(app_msg)) {
                    handled = true;
                    break;
                }
            }
        }

        if (!handled) {

            // @TODO: Send input to input handler
        }

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
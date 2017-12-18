#pragma once 

#include "../ZeroEngineStd.h"
#include "IGameView.h"
#include "IScreenElement.h"
#include "../Framework/IRenderer.h"
#include "../Input/Input.h"
#include "../Entity/Entity.h"
#include "../Process/ProcessManager.h"

namespace ZeroEngine {

    extern const uint32_t INVALID_PLAYER_NUMBER;

    class HumanView : public IGameView {
    private:
        // InputHandler
        // Audio
        uint32_t _player_number;
        GameViewId _view_id;
        GameViewType _view_type;
        ProcessManager* _process_manager;
        EntityId _entity_id;
        std::shared_ptr<IKeyboardHandler> _keyboard_handler;
        std::shared_ptr<IMouseHandler> _mouse_handler;

        // @TEMP 
        int _mouse_radius = 5;

        // process manager
        Tick _current_tick;
        Tick _last_draw;
        bool _is_full_speed;
        IRenderer::s_ptr _renderer;
        ScreenElementList _screen_elements;
        bool _is_paused;
        bool _is_initialized;
    public:
        HumanView(IRenderer::s_ptr);
        virtual ~HumanView();
        virtual bool restore() override;
        virtual bool lost_device() override;
        virtual bool render(Tick delta_time) override;
        virtual void update(Tick delta_time) override;
        virtual void attach(GameViewId view_id, EntityId entity_id) override;
        void initialize() override;
        virtual bool msg_proc(AppMsg::ptr app_msg) override;
        inline const GameViewId& get_id() const override { return _view_id; }
        inline const GameViewType& get_type() const override { return _view_type; }
        virtual StringRepr to_string() const override { return "HumanView"; }

        virtual void add_screen_element(IScreenElement::ptr);
        virtual void remove_screen_element(IScreenElement::ptr);
        inline virtual void initialize_audio() {}
        inline void toggle_pause() { _is_paused = !_is_paused; }
        inline virtual void render_text() {}
        inline bool load_game() { return on_load_game(); }
        inline uint32_t get_player_number() const { return _player_number; }
        inline void set_player_number(uint32_t number) { _player_number = number; }
        typedef std::shared_ptr<HumanView> ptr;
    protected:
        inline void set_mouse_handler(std::shared_ptr<IMouseHandler> handler);
        inline void set_keyboard_handler(std::shared_ptr<IKeyboardHandler> handler);
        inline void toggle_full_speed() { _is_full_speed = !_is_full_speed; }
        inline void set_full_speed(bool full_speed) { _is_full_speed = full_speed; }
        inline bool is_full_speed() const { return _is_full_speed; }
        inline Tick get_current_tick() const { return _current_tick; }
        inline Tick get_last_draw_time() const { return _last_draw; }
        inline IRenderer::s_ptr get_renderer() const { return _renderer; }
        inline const ScreenElementList& get_screen_elements() const { return _screen_elements; }
        inline virtual bool on_load_game() { return true; }
        inline virtual void on_register_event_delegates() {}
        inline virtual void on_unregister_event_delegates() {}
        inline virtual bool on_msg_proc(AppMsg::ptr msg, bool handled) { return false; }
    private:
        HumanView();
        HumanView(const HumanView&);
        void register_event_delegates();
        void unregister_event_delegates();
    };

    inline void HumanView::set_mouse_handler(std::shared_ptr<IMouseHandler> handler) {
        _mouse_handler = handler;
    }

    inline void HumanView::set_keyboard_handler(std::shared_ptr<IKeyboardHandler> handler) {
        _keyboard_handler = handler;
    }

}
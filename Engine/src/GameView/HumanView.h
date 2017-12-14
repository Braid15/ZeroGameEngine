#pragma once 

#include "../ZeroEngineStd.h"
#include "IGameView.h"
#include "IScreenElement.h"
#include "../Framework/IRenderer.h"
#include "../Input/Input.h"
#include "../Framework/Framework.h"
#include "../Entity/Entity.h"

namespace ZeroEngine {

    class HumanView : public IGameView {
    private:
        // InputHandler
        // Audio
        GameViewId _view_id;
        GameViewType _view_type;
        EntityId _entity_id;
        // process manager
        Tick _current_tick;
        Tick _last_draw;
        bool _is_full_speed;
        IRendererPtr _renderer;
        ScreenElementList _screen_elements;
        bool _is_paused;
    public:
        HumanView(IRendererPtr);
        virtual ~HumanView();
        virtual bool on_restore() override;
        virtual bool on_lost_device() override;
        virtual bool on_render(Tick delta_time) override;
        virtual void on_update(Tick delta_time) override;
        virtual void on_attach(GameViewId view_id, EntityId entity_id) override;
        virtual bool on_msg_proc(const AppMsg* const app_msg) override;
        inline const GameViewId& get_id() const override { return _view_id; }
        inline const GameViewType& get_type() const override { return _view_type; }
        virtual StringRepr to_string() const override { return "HumanView"; }

        virtual void add_screen_element(IScreenElementPtr);
        virtual void remove_screen_element(IScreenElementPtr);
        inline virtual void initialize_audio() {}
        inline void toggle_pause() { _is_paused = !_is_paused; }
        inline virtual void render_text() {}
        inline bool load_game() { return on_load_game(); }
    protected:
        inline void toggle_full_speed() { _is_full_speed = !_is_full_speed; }
        inline void set_full_speed(bool full_speed) { _is_full_speed = full_speed; }
        inline bool is_full_speed() const { return _is_full_speed; }
        inline Tick get_current_tick() const { return _current_tick; }
        inline Tick get_last_draw_time() const { return _last_draw; }
        inline IRendererPtr get_renderer() const { return _renderer; }
        inline const ScreenElementList& get_screen_elements() const { return _screen_elements; }
        inline virtual bool on_load_game() { return true; }
        inline virtual void on_register_event_delegates() {}
        inline virtual void on_unregister_event_delegates() {}
    private:
        HumanView();
        HumanView(const HumanView&);
        void register_event_delegates();
        void unregister_event_delegates();
    };

}
#pragma once

#include "../ZeroEngineStd.h"
#include "../GameView/GameView.h"
#include "IGameLogic.h"
#include "../Entity/Entity.h"
#include "../Entity/EntityManager.h"
#include "../Events/Events.h"
#include "../Physics/Physics.h"

namespace ZeroEngine {


    class BaseGameLogic : public IGameLogic {
    private:
        IPhysicsPtr _physics;
        Ticks _lifetime;
        EntityManager* _entity_manager;
        BaseGameState _current_state;
        GameViewList _game_views;
        bool _render_diagnostics;
        bool _is_proxy;
        int _human_players_attached;
        int _ai_players_attached;
        int _human_games_loaded;
    public:
        BaseGameLogic();
        virtual ~BaseGameLogic();
        virtual StringRepr to_string() const = 0;
        virtual bool initialize();
        virtual bool shutdown();
        bool load_game() override;
        bool load_game(const char* level_resource) override;
        bool load_game(const std::string level_resource) override;
        virtual void set_proxy() override;
        virtual void on_update(Ticks delta_time) override;
        virtual void change_state(IGameState state) override;
        virtual void change_state(BaseGameState state) override;
        virtual void move_entity(const EntityId& entity_id, const float x, const float y) override;
        virtual void move_entity(const EntityId& entity_id, const Point<float>& location) override;
        virtual void destroy_entity(const EntityId& entity_id) override;
        virtual void add_game_view(IGameViewPtr view, EntityId entity_id=INVALID_ENTITY_ID) override;
        virtual void remove_game_view(IGameViewPtr view) override;
        virtual WeakEntityPtr get_entity(const EntityId& entity_id) override;
        virtual EntityPtr create_entity() override;
        inline IPhysicsPtr get_physics() const override { return _physics; }
    protected:
        inline int get_human_players_attached() const { return _human_players_attached; }
        inline int get_ai_players_attached() const { return _ai_players_attached; }
        inline int get_human_games_loaded() const { return _human_games_loaded; }
        inline void set_human_players_attached(int players) { _human_players_attached = players; }
        inline void set_ai_layers_attached(int ai) { _ai_players_attached = ai; }
        inline void set_human_games_loaded(int games) { _human_games_loaded = games; }
        inline const BaseGameState& get_game_state() const { return _current_state; }
        inline bool is_rendering_diagnostics() const { return _render_diagnostics; }
        inline void set_render_diagnostics(bool render) { _render_diagnostics = render; }
        inline void toggle_render_diagnostics() { _render_diagnostics = !_render_diagnostics; }
        inline Ticks get_lifetime() const { return _lifetime; }
        inline virtual bool on_load_game() { return true; }

        // Should these be virtual or should the call virtual methods
        // that sub classes can override?
        void on_move_entity_delegate(IEventDataPtr event_data);
        void on_request_new_entity_delegate(IEventDataPtr event_data);
        void on_request_destroy_entity_delegate(IEventDataPtr event_data);
    };
}
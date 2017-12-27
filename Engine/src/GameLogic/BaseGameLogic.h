#pragma once

#include "../ZeroEngineStd.h"
#include "../GameView/GameViewInclude.h"
#include "IGameLogic.h"
#include "../Entity/Entity.h"
#include "../Entity/IEntityManager.h"
#include "../Entity/EntityManager.h"
#include "../Events/Events.h"
#include "../ZeroEngineEvents.h"
#include "../Physics/Physics.h"
#include "../Process/ProcessManager.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

namespace ZeroEngine {


    class BaseGameLogic : public IGameLogic {
    private:
        IPhysicsPtr _physics;
        Tick _lifetime;
        IEntityManager* _entity_manager;
        ProcessManager* _process_manager;
        BaseGameState _current_state;
        GameViewList _game_views;
        HumanView::ptr _human_view;
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
        virtual void render_diagnostics();
        bool load_game() override;
        bool load_game(const char* level_resource) override;
        bool load_game(const std::string level_resource) override;
        virtual void set_proxy() override;
        virtual void update(Tick delta_time) override;
        // virtual void change_state(IGameState state) override;
        virtual void change_state(BaseGameState state) override;

        virtual void move_entity(const EntityId& entity_id, const Vector2& pos) override;
        virtual void move_entity(const EntityId& entity_id, const Vector3& pos) override;
        virtual void move_entity(const EntityId& entity_id, const Vector4& pos) override;

        virtual void destroy_entity(const EntityId& entity_id) override;
        virtual void add_game_view(IGameViewPtr view, EntityId entity_id=INVALID_ENTITY_ID) override;
        virtual void remove_game_view(IGameViewPtr view) override;

        virtual WeakEntityPtr get_entity(const EntityId& entity_id) override;
        virtual EntityPtr create_entity() override;
        virtual EntityPtr create_entity(std::string resource_path) override;
        inline GameViewList get_game_views() { return _game_views; }
        inline IPhysicsPtr get_physics() const { return _physics; }
        inline uint32_t get_entity_count() const { return _entity_manager->get_entity_count(); }
    protected:
        inline const ProcessManager& get_process_manager() const { return *_process_manager; }
        inline void attach_process(Process::ptr process) const { _process_manager->attach_process(process); }
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
        inline Tick get_lifetime() const { return _lifetime; }

        void set_entity_manager(IEntityManager* manager);
        inline const IEntityManager& get_entity_manager() const { return *_entity_manager; }

        inline virtual bool on_load_game() { return true; }
        inline virtual void on_register_event_delegates() {}
        inline virtual void on_unregister_event_delegates() {}

        void move_entity_event_delegate(IEventDataPtr event_data);
        void request_create_entity_event_delegate(IEventDataPtr event_data);
        void request_destroy_entity_event_delegate(IEventDataPtr event_data);
        void attach_process_event_delegate(IEventDataPtr event_data);
    private:
        void destroy_all_entities();
        void load_game_views();
        void register_event_delegates();
        void unregister_event_delegates();
    };
}
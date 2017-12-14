#include "BaseGameLogic.h"

namespace ZeroEngine {

    BaseGameLogic::BaseGameLogic() {
        _physics = IPhysicsPtr(zero_new NullPhysics());
        _lifetime = 0;
        _entity_manager = zero_new NullEntityManager();
        _current_state = BaseGameState::invalid;
        _render_diagnostics = false;
        _is_proxy = false;
        _human_players_attached = 0;
        _ai_players_attached = 0;
        _human_games_loaded = 0;
    }

    BaseGameLogic::~BaseGameLogic() {
        while (!_game_views.empty()) {
            _game_views.pop_front();
        }
        zero_delete(_entity_manager);
        _current_state = BaseGameState::invalid;
    }

    bool BaseGameLogic::initialize() {
        bool success = true;
        register_event_delegates();
        return success;
    }

    bool BaseGameLogic::shutdown() {
        bool success = true;
        _entity_manager->shutdown();
        unregister_event_delegates();
        return success;
    }

    // @TODO: I don't necessarily like this
    void BaseGameLogic::render_diagnostics() {
        if (_render_diagnostics) {
            _physics->render_diagnostics();
        }
    }

    bool BaseGameLogic::load_game() {
        load_game_views();
        return on_load_game();
    }

    bool BaseGameLogic::load_game(const char* level_resource) {
        bool success = true;
        return success;
    }

    bool BaseGameLogic::load_game(const std::string level_resource) {
        bool success = true;
        return success;
    }

    void BaseGameLogic::set_proxy() {
        _is_proxy = true;
        // @TODO: Finish
    }

    void BaseGameLogic::on_update(Ticks delta_time) {
        _lifetime += delta_time;

        // @TODO: Handle different BaseGameStates

        if (_physics && !_is_proxy) {
            _physics->on_update(delta_time);
            _physics->sync_visible_scene();
        }

        for (GameViewList::iterator iter = _game_views.begin(); iter != _game_views.end(); ++iter) {
            (*iter)->on_update(delta_time);
        }

        _entity_manager->update_entities(delta_time);
    }

    void BaseGameLogic::change_state(BaseGameState state) {
        // @TODO: Handle different states
        _current_state = state;
    }

    void BaseGameLogic::move_entity(const EntityId& entity_id, const float x, const float y) {
        std::cout << "BaseGameLogic::move_entity\n";

    }

    void BaseGameLogic::move_entity(const EntityId& entity_id, const Point<float>&location) {
        std::cout << "BaseGameLogic::move_entity\n";
    }

    void BaseGameLogic::destroy_entity(const EntityId& entity_id) {
        ZeroEventManager::trigger_event(EntityDestroyedEvent::create(entity_id));
        _entity_manager->destroy_entity(entity_id);
    }

    void BaseGameLogic::add_game_view(IGameViewPtr view, EntityId entity_id) {
        int view_id = static_cast<int>(_game_views.size());
        _game_views.push_back(view);
        view->on_attach(view_id, entity_id);
        view->on_restore();
    }

    void BaseGameLogic::remove_game_view(IGameViewPtr view) {
        _game_views.remove(view);
    }

    WeakEntityPtr BaseGameLogic::get_entity(const EntityId& entity_id) {
        return _entity_manager->get_entity(entity_id);
    }

    EntityPtr BaseGameLogic::create_entity() {
        return _entity_manager->create_entity();
    }

    //
    // Protected members
    //

    void BaseGameLogic::move_entity_event_delegate(IEventDataPtr event_data) {
        MoveEntityEvent::ptr data = MoveEntityEvent::cast(event_data);
        move_entity(data->get_entity_id(), data->get_new_location());
    }

    void BaseGameLogic::request_new_entity_event_delegate(IEventDataPtr event_data) {
        if (!_is_proxy) {
            RequestCreateEntityEvent::ptr data = RequestCreateEntityEvent::cast(event_data);
            EntityPtr entity = _entity_manager->create_entity();
            ZeroEventManager::queue_event(EntityCreatedEvent::create(entity->get_id()));
        }
    }

    void BaseGameLogic::request_destroy_entity_event_delegate(IEventDataPtr event_data) {
        RequestDestroyEntityEvent::ptr data = RequestDestroyEntityEvent::cast(event_data);
        destroy_entity(data->get_entity_id());
    }


    //
    // Private members
    //

    void BaseGameLogic::load_game_views() {
        // @TODO: Implement HumanView
        /*
        for (GameViewList::iterator iter = _game_views.begin(); iter != _game_views.end(); ++iter) {
            IGameViewPtr view = *iter;
            if (view->get_type() == GameViewType::human) {
                std::shared_ptr<HumanView> human_view = std::static_pointer_cast<HumanView, IGameView>(view);
                human_view->load_game();
            }
        }
        */
    }

    void BaseGameLogic::register_event_delegates() {
        ZeroEventManager::register_listener(
            fastdelegate::MakeDelegate(this, &BaseGameLogic::request_destroy_entity_event_delegate),
            RequestDestroyEntityEvent::type);
        on_register_event_delegates();
    }

    void BaseGameLogic::unregister_event_delegates() {
        ZeroEventManager::unregister_listener(
            fastdelegate::MakeDelegate(this, &BaseGameLogic::request_destroy_entity_event_delegate),
            RequestDestroyEntityEvent::type);
        on_unregister_event_delegates();
    }








}
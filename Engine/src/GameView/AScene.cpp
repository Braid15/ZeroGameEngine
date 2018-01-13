#include "AScene.h"
#include "../AppLayer/Game.h"


namespace ZeroEngine {

    using std::shared_ptr;
    using std::static_pointer_cast;
    using fastdelegate::MakeDelegate;

    AScene::AScene(shared_ptr<IRenderer> renderer) {
        _renderer = renderer;

        ZeroEventManager::register_listener(MakeDelegate(this, &AScene::modifed_render_component_delegate),
                                            ModifiedRenderComponentEvent::type);
        ZeroEventManager::register_listener(MakeDelegate(this, &AScene::new_render_component_delegate),
                                            NewRenderComponentEvent::type);
        ZeroEventManager::register_listener(MakeDelegate(this, &AScene::move_entity_event_delegate),
                                            MoveEntityEvent::type);
        ZeroEventManager::register_listener(MakeDelegate(this, &AScene::entity_destroyed_event_delegate),
                                            EntityDestroyedEvent::type);
    }

    AScene::~AScene() {
        ZeroEventManager::unregister_listener(MakeDelegate(this, &AScene::modifed_render_component_delegate),
                                              ModifiedRenderComponentEvent::type);
        ZeroEventManager::unregister_listener(MakeDelegate(this, &AScene::new_render_component_delegate),
                                              NewRenderComponentEvent::type);
        ZeroEventManager::unregister_listener(MakeDelegate(this, &AScene::move_entity_event_delegate),
                                              MoveEntityEvent::type);
        ZeroEventManager::unregister_listener(MakeDelegate(this, &AScene::entity_destroyed_event_delegate),
                                              EntityDestroyedEvent::type);
    }

    bool AScene::render() {
        if (_root_node) {
            if (_root_node->pre_render(this)) {
                _root_node->render(this);
                _root_node->render_children(this);
                _root_node->post_render(this);
            }
        }

        return true;
    }

    bool AScene::restore() {
        if (!_root_node) {
            return true;
        }
        _renderer->on_restore();
        return _root_node->restore(this);
    }

    bool AScene::on_lost_device() {
        if (!_root_node) {
            return true;
        }

        return _root_node->on_lost_device(this);
    }

    bool AScene::update(Tick delta_time) {
        if (!_root_node) {
            return true;
        }

        static Tick last_time = Game::get_ticks();
        Tick elapsed_time = 0;
        Tick now = Game::get_ticks();

        elapsed_time = now - last_time;
        last_time = now;

        return _root_node->update(this, elapsed_time);
    }

    std::shared_ptr<ISceneNode> AScene::find_entity(const EntityId& id) {
        std::map<EntityId, shared_ptr<ISceneNode>>::iterator entity = _entity_map.find(id);
        if (entity == _entity_map.end()) {
            return std::shared_ptr<ISceneNode>();
        }

        return entity->second;
    }

    bool AScene::add_child(const EntityId& id, shared_ptr<ISceneNode> node) {
        if (id != invalid_entity_id()) {
            _entity_map[id] = node;
        }

        LOG_TODO("AScene", "Add lights");

        return _root_node->add_child(node);
    }

    bool AScene::remove_child(const EntityId& id) {
        if (id == invalid_entity_id()) {
            return false;
        }

        shared_ptr<ISceneNode> child = find_entity(id);

        if (child) {
            _entity_map.erase(id);
            return _root_node->remove_child(id);
        }
        return false;
    }

    void AScene::new_render_component_delegate(shared_ptr<IEventData> data_ptr) {
        assert(data_ptr->get_event_type() == NewRenderComponentEvent::type);

        shared_ptr<NewRenderComponentEvent> data = static_pointer_cast<NewRenderComponentEvent>(data_ptr);

        shared_ptr<SceneNode> node = data->get_scene_node();

        if (!node->restore(this)) {
            LOG_DEBUG("AScene", "Failed to restore scene node");
            return;
        }

        add_child(data->get_entity_id(), node);
    }

    void AScene::modifed_render_component_delegate(shared_ptr<IEventData> data_ptr) {
        assert(data_ptr->get_event_type() == ModifiedRenderComponentEvent::type);

        shared_ptr<ModifiedRenderComponentEvent> data = static_pointer_cast<ModifiedRenderComponentEvent>(data_ptr);
    }

    void AScene::entity_destroyed_event_delegate(shared_ptr<IEventData> data_ptr) {
        assert(data_ptr->get_event_type() == EntityDestroyedEvent::type);

        shared_ptr<EntityDestroyedEvent> data = static_pointer_cast<EntityDestroyedEvent>(data_ptr);
        remove_child(data->get_entity_id());
    }

    void AScene::move_entity_event_delegate(shared_ptr<IEventData> data_ptr) {
        assert(data_ptr->get_event_type() == MoveEntityEvent::type);

        shared_ptr<MoveEntityEvent> data = static_pointer_cast<MoveEntityEvent>(data_ptr);

        EntityId id = data->get_entity_id();
        Transform transform = data->get_transform();

        shared_ptr<ISceneNode> node = find_entity(id);

        if (node) {
            node->set_transform(&transform);
        }
    }

    void AScene::set_camera(shared_ptr<CameraNode> camera) {
        _camera = camera;
    }

    bool AScene::raycast(IRayCast* raycast) {
        LOG_UNIMPLEMENTED();
        return true;
    }

}
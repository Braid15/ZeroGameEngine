#pragma once

#include "../ZeroEngineStd.h"
#include "ISceneNode.h"
#include "SceneNode.h"
#include "../Time.h"
#include "../Entity/EntityId.h"
#include "../Events/Events.h"
#include "../ZeroEngineEvents.h"

namespace ZeroEngine {

    class IEventData;
    class IRayCast;
    class IRenderer;
    class CameraNode;

    class AScene {
    protected:
        std::shared_ptr<SceneNode> _root_node;
        std::shared_ptr<CameraNode> _camera;
        std::shared_ptr<IRenderer> _renderer;
        std::map<EntityId, std::shared_ptr<ISceneNode>> _entity_map;

        virtual void on_register_delegates() {}
        virtual void on_unregister_delegates() {}

    public:
        AScene(std::shared_ptr<IRenderer>);
        virtual ~AScene();

        virtual bool render();
        virtual bool restore();
        virtual bool on_lost_device();
        virtual bool update(Tick delta_time);
        virtual std::shared_ptr<ISceneNode> find_entity(const EntityId&);
        virtual bool add_child(const EntityId&, std::shared_ptr<ISceneNode>);
        virtual bool remove_child(const EntityId&);
        virtual bool raycast(IRayCast*);
        
        virtual void set_camera(std::shared_ptr<CameraNode>);

        virtual void new_render_component_delegate(std::shared_ptr<IEventData>);
        virtual void modifed_render_component_delegate(std::shared_ptr<IEventData>);
        virtual void move_entity_event_delegate(std::shared_ptr<IEventData>);
        virtual void entity_destroyed_event_delegate(std::shared_ptr<IEventData>);

        inline std::shared_ptr<IRenderer> get_renderer() const { return _renderer; }
    };
}


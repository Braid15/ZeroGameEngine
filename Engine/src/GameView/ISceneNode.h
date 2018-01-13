#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Entity/EntityId.h"

namespace ZeroEngine {

    class Transform;
    class AScene;
    class IRayCast;
    struct SceneNodeProperties;

    class ISceneNode {
    public:

        virtual EntityId get_entity_id() const = 0;
        virtual void set_transform(const Transform* to_world, const Transform* from_world=nullptr) = 0;
        virtual bool update(AScene* scene, Tick delta_time) = 0;
        virtual bool restore(AScene* scene) = 0;
        virtual bool pre_render(AScene* scene) = 0;
        virtual bool is_visible(AScene* scene) = 0;
        virtual bool render(AScene* scene) = 0;
        virtual bool render_children(AScene* scene) = 0;
        virtual bool post_render(AScene* scene) = 0;

        virtual bool add_child(std::shared_ptr<ISceneNode> child) = 0;
        virtual bool remove_child(const EntityId& id) = 0;
        virtual bool on_lost_device(AScene* scene) = 0;
        virtual bool on_raycast(AScene* scene, IRayCast* raycast) = 0;

        virtual ~ISceneNode() {}

    };
}
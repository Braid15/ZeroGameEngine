#pragma once

#include "../ZeroEngineStd.h"
#include "ISceneNode.h"
#include "../Entity/EntityId.h"
#include "../Entity/Transform.h"
#include "../Math/MathTypes.h"

namespace ZeroEngine {


    // -------------------
    // SceneNodeProperties
    // -------------------

    struct SceneNodeProperties {
        EntityId entity_id;
        Transform to_world_transform;
        Transform from_world_transform;
        Float32 radius;

        SceneNodeProperties();
    };

    // ---------
    // SceneNode
    // ---------

    class BaseRenderComponent;
    class IRayCast;

    class SceneNode : public ISceneNode {
    private:
        typedef std::vector<std::shared_ptr<ISceneNode>> ChildrenNodeList;
        ChildrenNodeList _child_nodes;
        SceneNode* _parent;
        SceneNodeProperties _properties;
        BaseRenderComponent* _render_component;
    protected:
        virtual void set_parent(SceneNode* parent) { _parent = parent; }
        virtual void set_render_component(BaseRenderComponent* component) { _render_component = component; }
        std::vector<std::shared_ptr<ISceneNode>>& get_children() { return _child_nodes; }
        SceneNode* get_parent() { return _parent; }
        BaseRenderComponent* get_render_component() { return _render_component; }

    public:
        SceneNode(EntityId, BaseRenderComponent*, Transform* to_world, Transform* from_world=nullptr);

        virtual ~SceneNode() {}

        virtual void set_transform(const Transform* to_world, const Transform* from_world=nullptr) override;
        virtual bool update(AScene* scene, Tick delta_time) override;
        virtual bool restore(AScene* scene) override;
        virtual bool pre_render(AScene* scene) override;
        virtual bool is_visible(AScene* scene) override;
        virtual bool render(AScene* scene) override;
        virtual bool render_children(AScene* scene) override;
        virtual bool post_render(AScene* scene) override;

        virtual bool add_child(std::shared_ptr<ISceneNode> child) override;
        virtual bool remove_child(const EntityId& id) override;
        virtual bool on_lost_device(AScene* scene) override;
        virtual bool on_raycast(AScene* scene, IRayCast* raycast) override;

        Vector3 get_position() const { return _properties.to_world_transform.get_position(); }
        void set_position(const Vector3& pos) { _properties.to_world_transform.set_position(pos); }

        EntityId get_entity_id() const { return _properties.entity_id; }

        Vector3 get_world_position() const;

        Vector3 get_direction() const;

        void set_radius(const Float32 radius) { _properties.radius = radius; }
    };
}
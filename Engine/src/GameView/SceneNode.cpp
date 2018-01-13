#include "SceneNode.h"
#include "../AppLayer/Game.h"
#include "../Entity/Entity.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    // -------------------
    // SceneNodeProperties
    // -------------------

    SceneNodeProperties::SceneNodeProperties() {
        entity_id = invalid_entity_id();
        radius = 0.0f;
    }

    /*
    void SceneNodeProperties::transform(Transform* to_world, Transform* from_world) const {
        if (to_world) {
            *to_world = _to_world;
        }

        if (from_world) {
            *from_world = _from_world;
        }
    }
    */


    // ---------
    // SceneNode
    // ---------

    SceneNode::SceneNode(EntityId entity_id, BaseRenderComponent* render_component, Transform* to_world, Transform* from_world) {
        assert(render_component);

        _parent = nullptr;
        _properties.entity_id = entity_id;
        _render_component = render_component;
        set_transform(to_world, from_world);
        set_radius(0.0f);
    }

    void SceneNode::set_transform(const Transform* to_world, const Transform* from_world) {
        assert(to_world);

        _properties.to_world_transform = *to_world;

        if (from_world) {
            _properties.from_world_transform = *from_world;
        } else {
            _properties.from_world_transform = _properties.to_world_transform.get_inverse();
        }
    }

    bool SceneNode::update(AScene* scene, Tick delta_time) {
        assert(scene);

        ChildrenNodeList::iterator node = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (node != end) {
            (*node)->update(scene, delta_time);
            node++;
        }
        return true;
    }

    bool SceneNode::restore(AScene* scene) {
        assert(scene);
        // Set color

        ChildrenNodeList::iterator node = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (node != end) {
            (*node)->restore(scene);
            node++;
        }
        return true;
    }

    bool SceneNode::pre_render(AScene* scene) {
        assert(scene);

        std::shared_ptr<Entity> entity = Game::get_entity(_properties.entity_id).lock();
        if (entity) {
            _properties.to_world_transform = entity->get_transform();
        }

        LOG_TODO("SceneNode", "scene->push_and_set_matrix()");
        //scene->push_and_set_matrix(_properties._to_world);
        return true;
    }

    bool SceneNode::is_visible(AScene* scene) {
        assert(scene);

        LOG_TODO("SceneNode", "IMplement Frustrum");
        return true;
    }

    bool SceneNode::render(AScene* scene) {
        return true;
    }

    bool SceneNode::render_children(AScene* scene) {
        assert(scene);

        ChildrenNodeList::iterator child = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (child != end) {
            if ((*child)->pre_render(scene)) {
                if ((*child)->is_visible(scene)) {
                    // Check alpha for transparency

                    (*child)->render_children(scene);
                }
            }

            (*child)->post_render(scene);
            child++;
        }

        return true;
    }

    bool SceneNode::post_render(AScene* scene) {
        assert(scene);
        LOG_TODO("SceneNode", "scene->pop_matrix()");
        return true;
    }

    bool SceneNode::add_child(std::shared_ptr<ISceneNode> child) {
        _child_nodes.push_back(child);

        std::shared_ptr<SceneNode> cast_child = std::static_pointer_cast<SceneNode>(child);
        cast_child->set_parent(this);

        LOG_TODO("SceneNode", "Set new radius");
        return true;
    }

    bool SceneNode::remove_child(const EntityId& id) {
        if (id == invalid_entity_id()) {
            return false;
        }

        ChildrenNodeList::iterator node = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (node != end) {
            EntityId entity_id = (*node)->get_entity_id();
            if (entity_id != invalid_entity_id() && entity_id == id) {
                _child_nodes.erase(node);
                return true;
            }
            node++;
        }

        return false;
    }

    bool SceneNode::on_lost_device(AScene* scene) {
        assert(scene);

        ChildrenNodeList::iterator node = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (node != end) {
            (*node)->on_lost_device(scene);
            node++;
        }

        return true;
    }

    bool SceneNode::on_raycast(AScene* scene, IRayCast* raycast) {
        assert(scene && raycast);

        ChildrenNodeList::iterator node = _child_nodes.begin();
        ChildrenNodeList::iterator end = _child_nodes.end();

        while (node != end) {
            if (!(*node)->on_raycast(scene, raycast)) {
                return false;
            }
        }

        return true;
    }

    Vector3 SceneNode::get_world_position() const {
        Vector3 pos = get_position();
        if (_parent) {
            pos += _parent->get_world_position();
        }

        return pos;
    }

    Vector3 SceneNode::get_direction() const {
        return _properties.to_world_transform.get_direction();
    }
}


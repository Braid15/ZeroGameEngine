#include "BaseRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Events/EventManager.h"
#include "../../ZeroEngineEvents.h"
#include "../../Utils/StringId.h"

namespace ZeroEngine {

    class SceneNode;
    using std::shared_ptr;
    using std::make_shared;

    bool BaseRenderComponent::initialize(const XmlReader& reader) {
        return on_initialize(reader);
    }

    void BaseRenderComponent::post_initialize() {
        shared_ptr<SceneNode> node(get_scene_node());
        shared_ptr<NewRenderComponentEvent> event_data = make_shared<NewRenderComponentEvent>(get_owner()->get_id(), node);
        ZeroEventManager::trigger_event(event_data);
    }

    void BaseRenderComponent::on_write_xml(const XmlWriter& writer) {
        write_inherited_xml(writer);
    }

    shared_ptr<SceneNode> BaseRenderComponent::get_scene_node() {
        if (!_scene_node) {
            _scene_node = create_scene_node();
        }

        return _scene_node;
    }
}
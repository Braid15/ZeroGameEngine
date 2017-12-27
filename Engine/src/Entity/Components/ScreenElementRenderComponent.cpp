#include "ScreenElementRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Events/EventManager.h"
#include "../../ZeroEngineEvents.h"

namespace ZeroEngine {

    const char* ScreenElementRenderComponent::name = "ScreenElementRenderComponent";

    EntityComponent* ScreenElementRenderComponent::create() {
        return zero_new ScreenElementRenderComponent();
    }

    ScreenElementRenderComponent::ScreenElementRenderComponent() {
        set_entity_id(static_cast<EntityComponentId>(Hash::hash(name)));
    }


    ScreenElementRenderComponent::ScreenElementRenderComponent(std::shared_ptr<IScreenElement> element) {
        set_entity_id(static_cast<EntityComponentId>(Hash::hash(name)));
        _screen_element = element;
    }

    ScreenElementRenderComponent::~ScreenElementRenderComponent() {
    }

    bool ScreenElementRenderComponent::initialize(const XmlReader& reader) {
        return on_initialize(reader);
    }

    void ScreenElementRenderComponent::post_initialize() {
        ZeroEventManager::trigger_event(
            ScreenElementRenderComponentCreatedEvent::create(_screen_element));

        on_post_initialize();
    }

    void ScreenElementRenderComponent::on_write_xml(const XmlWriter& writer) {
        on_write_xml_delegate(writer);
    }
}
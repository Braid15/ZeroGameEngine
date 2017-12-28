#include "ScreenElementRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Events/EventManager.h"
#include "../../ZeroEngineEvents.h"

namespace ZeroEngine {

    const char* ScreenElementRenderComponent::name = "ScreenElementRenderComponent";
    const EntityComponentId ScreenElementRenderComponent::id = Hash::hash(ScreenElementRenderComponent::name);

    EntityComponent* ScreenElementRenderComponent::create() {
        return zero_new ScreenElementRenderComponent();
    }

    ScreenElementRenderComponent::ScreenElementRenderComponent(std::shared_ptr<IScreenElement> element) {
        _screen_element = element;
    }

    ScreenElementRenderComponent::~ScreenElementRenderComponent() {
        ZeroEventManager::trigger_event(
            ScreenElementRenderComponentDestroyedEvent::create(_screen_element));
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
        LOG_TODO("ScreenElementRenderComponent", "There will be issues when writing xml with derived types");
        on_write_xml_delegate(writer);
    }
}
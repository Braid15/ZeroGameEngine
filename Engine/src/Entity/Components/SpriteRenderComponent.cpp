#include "SpriteRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Events/EventManager.h"

namespace ZeroEngine {

    const char* SpriteRenderComponent::name = "SpriteRenderComponent";

    SpriteRenderComponent::SpriteRenderComponent() {
        set_entity_id(static_cast<EntityComponentId>(Hash::hash(name)));
    }

    EntityComponent* SpriteRenderComponent::create() {
        return zero_new SpriteRenderComponent();
    }

    bool SpriteRenderComponent::on_initialize(const XmlReader& reader) {
        assert(strcmp(reader.get_element_name(), name) == 0);

        if (!reader.move_to_element("Texture")) return false;
        _texture_resource_path = std::string(reader.get_element_attribute_value("resource"));

        _sprite = std::shared_ptr<Sprite>(zero_new Sprite(_texture_resource_path));
        _sprite->load();

        set_screen_element(_sprite);

        return true;
    }

    void SpriteRenderComponent::on_write_xml_delegate(const XmlWriter& writer) {
        writer.write_start_element(name);

        writer.write_start_element("Texture");
        writer.write_attribute_string("resource", _texture_resource_path.c_str());
        writer.write_end_element();

        writer.write_end_element();
    }

}
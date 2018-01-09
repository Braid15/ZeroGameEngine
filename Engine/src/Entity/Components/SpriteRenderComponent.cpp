#include "SpriteRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Events/EventManager.h"
#include "../Components/TransformComponent2D.h"

namespace ZeroEngine {

    const char* SpriteRenderComponent::name = "SpriteRenderComponent";
    const EntityComponentId SpriteRenderComponent::id = STRING_ID("SpriteRenderComponent");

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

    void SpriteRenderComponent::update(Tick delta_time) {
        LOG_TODO("SpriteRenderComponent", "This should be done via events maybe??");
        LOG_TODO("SpriteRenderComponent", "This functionality should be in ScreenElementRenderComponent");

        auto component = get_owner()->get_component<TransformComponent2D>(TransformComponent2D::id).lock();
        if (component) {
            LOG_TODO("SpriteRenderComponent", "REFACTOR!");
            /*
            Vector3 size(_sprite->get_width(), _sprite->get_height(), 1.0f);
            Vector3 position(_sprite->get_position(), 1.0f);

            Matrix3x3 world_transform = component->get_world_transform();

            size.transform_by_matrix(world_transform);
            position.transform_by_matrix(world_transform);

            _sprite->set_position(position);
            _sprite->set_height(size.get_y());
            _sprite->set_width(size.get_x());
            */
            if (component->get_position() != _sprite->get_position()) {
                _sprite->set_position(component->get_position());
            }
        } else {
            LOG_DEBUG("SpriteRenderComponent", "Error finding TransformComponent2D on actor " + std::string(get_owner()->get_name()));
        }
    }

    void SpriteRenderComponent::on_write_xml_delegate(const XmlWriter& writer) {
        writer.write_start_element(name);

        writer.write_start_element("Texture");
        writer.write_attribute_string("resource", _texture_resource_path.c_str());
        writer.write_end_element();

        writer.write_end_element();
    }

}
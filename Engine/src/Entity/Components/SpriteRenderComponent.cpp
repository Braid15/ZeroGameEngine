#include "SpriteRenderComponent.h"
#include "../../Utils/Hash.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Events/EventManager.h"

namespace ZeroEngine {

    const char* TextureRenderComponent_2D::name = "TextureRenderComponent_2D";
    const EntityComponentId TextureRenderComponent_2D::id = STRING_ID("TextureRenderComponent_2D");

    EntityComponent* TextureRenderComponent_2D::create() {
        return zero_new TextureRenderComponent_2D();
    }

    bool TextureRenderComponent_2D::initialize_delegate(const XmlReader& reader) {
        assert(strcmp(reader.get_element_name(), name) == 0);
        if (!reader.move_to_element("Texture")) return false;

        _texture_resource_path = std::string(reader.get_element_attribute_value("resource"));

        return true;
    }

    std::shared_ptr<SceneNode> TextureRenderComponent_2D::create_scene_node() {
        LOG_UNIMPLEMENTED();
        // TextureSceneNode
        return std::shared_ptr<SceneNode>();
    }


    void TextureRenderComponent_2D::write_inherited_xml(const XmlWriter& writer) {
        writer.write_start_element(name);

        writer.write_start_element("Texture");
        writer.write_attribute_string("resource", _texture_resource_path.c_str());
        writer.write_end_element();

        writer.write_end_element();
    }

}
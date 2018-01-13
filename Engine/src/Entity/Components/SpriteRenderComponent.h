#pragma once

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"
#include "../Components/BaseRenderComponent.h"
#include "../../GameView/Sprite.h"

namespace ZeroEngine {

    class TextureRenderComponent_2D : public BaseRenderComponent {
    private:
        std::string _texture_resource_path;

    protected:
        virtual std::shared_ptr<SceneNode> create_scene_node() override;
        virtual bool initialize_delegate(const XmlReader&) override;
    public:
        TextureRenderComponent_2D() = default;
        virtual ~TextureRenderComponent_2D() {}

        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();

        virtual const EntityComponentId& get_id() const override { return id; }

        virtual inline const char* get_name() const override { return name; }
        virtual inline StringRepr to_string() const override { return "TextureRenderComponent_2D"; }
    private:
        virtual void write_inherited_xml(const XmlWriter& writer) override;
    };
}
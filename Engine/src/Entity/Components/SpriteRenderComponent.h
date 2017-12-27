#pragma once

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"
#include "ScreenElementRenderComponent.h"
#include "../../GameView/Sprite.h"

namespace ZeroEngine {

    class SpriteRenderComponent : public ScreenElementRenderComponent {
    private:
        std::shared_ptr<Sprite> _sprite;
        std::string _texture_resource_path;

    public:
        SpriteRenderComponent();
        virtual ~SpriteRenderComponent() {}
        static const char* name;
        static EntityComponent* create();

        virtual bool on_initialize(const XmlReader&) override;

        virtual inline const char* get_name() const override { return name; }
        virtual inline StringRepr to_string() const override { return "SpriteRenderComponet"; }
    private:
        virtual void on_write_xml_delegate(const XmlWriter& writer) override;
    };
}
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
        SpriteRenderComponent() = default;
        virtual ~SpriteRenderComponent() {}

        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();

        virtual const EntityComponentId& get_id() const override { return id; }

        virtual bool on_initialize(const XmlReader&) override;
        virtual void update(Tick delta_time) override;

        virtual inline const char* get_name() const override { return name; }
        virtual inline StringRepr to_string() const override { return "SpriteRenderComponent"; }
    private:
        virtual void on_write_xml_delegate(const XmlWriter& writer) override;
    };
}
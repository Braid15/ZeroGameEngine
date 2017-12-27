#pragma once 

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"

namespace ZeroEngine {

    class IScreenElement;

    class ScreenElementRenderComponent : public EntityComponent {
    private:
        std::shared_ptr<IScreenElement> _screen_element;
    public:
        ScreenElementRenderComponent() = default;
        virtual ~ScreenElementRenderComponent();

        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();

        explicit ScreenElementRenderComponent(std::shared_ptr<IScreenElement> element);

        virtual const EntityComponentId& get_id() const { return id; }

        bool initialize(const XmlReader&) override;
        inline virtual bool on_initialize(const XmlReader&) { return true; }
        inline virtual void update(Tick delta_time) override {}

        void post_initialize() override;

        inline virtual void on_post_initialize() {}

        virtual inline const char* get_name() const override { return name; }
        virtual inline StringRepr to_string() const { return "ScreenElementRenderComponent"; }

        std::shared_ptr<IScreenElement> get_screen_element() const { return _screen_element; }

        // @TODO: Protected??
        void set_screen_element(std::shared_ptr<IScreenElement> element) { _screen_element = element; }
    private:
        ScreenElementRenderComponent(const ScreenElementRenderComponent&) {}

        void on_write_xml(const XmlWriter& writer) override;
        virtual void on_write_xml_delegate(const XmlWriter& writer) {}
    };
}
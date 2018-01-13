#pragma once 

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"

namespace ZeroEngine {

    class SceneNode;

    class BaseRenderComponent : public EntityComponent {
    protected:
        std::shared_ptr<SceneNode> _scene_node;
    protected:
        virtual bool initialize_delegate(const XmlReader&) { return true; }
        virtual std::shared_ptr<SceneNode> create_scene_node() = 0;
        virtual void write_inherited_xml(const XmlWriter& writer) {}
    public:
        std::shared_ptr<SceneNode> get_scene_node();


        bool initialize(const XmlReader&) override;
        inline virtual bool on_initialize(const XmlReader&) { return true; }
        void post_initialize() override;
    private:
        void on_write_xml(const XmlWriter& writer) override;
    };
}
#pragma once

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"
#include "../../Math/MathTypes.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Utils/Xml/XmlReader.h"

namespace ZeroEngine {

    // @TODO: Make one transform class which takes care of 2D and 3D so client
    // code doesn't need to worry about the dimensions
    class TransformComponent2D final : public EntityComponent {
    private:
        Matrix3x3 _transform;

        // @TODO: rotation
    public:
        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();


        bool initialize(const XmlReader&) override;
        void post_initialize() override;
        inline const char* get_name() const override { return name; }
        inline StringRepr to_string() const { return "TransformComponent2D"; }

        inline const EntityComponentId& get_id() const override { return id; }

        inline const Matrix3x3& get_transform() const { return _transform; }
        inline void set_transform(const Matrix3x3& pos) { _transform = pos; }
    private:
        void on_write_xml(const XmlWriter& writer) override;
    };
}
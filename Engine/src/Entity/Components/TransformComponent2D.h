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
        Vector3 _position;

        // @TODO: rotation
    public:
        TransformComponent2D() : _transform(Matrix3x3::identity()), 
            _position(Vector3::unit_k()) {}
        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();


        bool initialize(const XmlReader&) override;
        void post_initialize() override;
        inline const char* get_name() const override { return name; }
        inline StringRepr to_string() const { return "TransformComponent2D"; }

        inline const EntityComponentId& get_id() const override { return id; }

        inline Vector2 get_position() const { 
            return Vector2(_transform[0][Axis::z], _transform[1][Axis::z]); 
        }

        inline const Matrix3x3& get_matrix() const { return _transform; }

        inline void set_matrix(const Matrix3x3& mat) { 
            _transform = _transform * mat; 
        }

    private:
        void on_write_xml(const XmlWriter& writer) override;
    };
}
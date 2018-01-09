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
        Vector3 _position;
        Degree _rotation;
        Vector3 _scale;
    public:
        TransformComponent2D() : 
            _position(Vector3(0, 0, 1)), _rotation(0.0f), 
            _scale(Vector3(1, 1, 1)) {}

        static const EntityComponentId id;
        static const char* name;
        static EntityComponent* create();


        bool initialize(const XmlReader&) override;
        void post_initialize() override;
        inline const char* get_name() const override { return name; }
        inline StringRepr to_string() const { return "TransformComponent2D"; }

        inline const EntityComponentId& get_id() const override { return id; }

        inline Vector2 get_position() const { 
            return Vector2(_position);
        }

        inline void set_position(const Vector2& pos) {
            _position.set(pos);
        }

        inline const Matrix3x3& get_world_transform() const { 
            return Matrix3x3::get_scaling_2D(_scale) 
                * Matrix3x3::get_rotation_2D(_position, _rotation)
                * Matrix3x3::get_translation_2D(_position);
        }

        inline void set_world_transform(const Matrix3x3& mat) { 
            _position.transform_by_matrix(mat);
        }

    private:
        void on_write_xml(const XmlWriter& writer) override;
    };
}
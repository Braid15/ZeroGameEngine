#pragma once

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"
#include "../../Math/Vector2.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Utils/Xml/XmlReader.h"

namespace ZeroEngine {

    class TransformComponent2D final : public EntityComponent {
    private:
        Vector2 _position;
        Vector2 _velocity;
        // @TEMP
        EntityComponentId _id = 0;

        // @TODO: rotation
    public:
        static const char* name;
        static EntityComponent* create(const XmlReader&);
        bool initialize() override;
        void post_initialize() override;
        const EntityComponentId& get_id() const override;
        inline const char* get_name() const override {return name; }
        inline StringRepr to_string() const { return "TransformComponent2D"; }

        inline const Vector2& get_position() const { return _position; }
        inline void set_position(const Vector2 pos) { _position = pos; }

        inline const Vector2& get_velocity() const { return _velocity; }
        inline void set_velocity(const Vector2 vel) { _velocity = vel; }
    private:
        void on_write_xml(const XmlWriter& writer) override;
    };
}
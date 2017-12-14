#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Graphics/Graphics.h"
#include "../Entity/Entity.h"
#include "../GameView/GameViewInclude.h"
#include "../Physics/Physics.h"

namespace ZeroEngine {

    class IGameState;

    enum class BaseGameState {
        invalid,
        running,
    };

    class IGameLogic : public IZeroObject {
    public:
        virtual bool load_game() = 0;
        virtual bool load_game(const char* level_resource) = 0;
        virtual bool load_game(const std::string level_resource) = 0;
        virtual void set_proxy() = 0;
        virtual void on_update(Tick delta_time) = 0;
        //virtual void change_state(IGameState) = 0;
        virtual void change_state(BaseGameState) = 0;
        virtual void move_entity(const EntityId& entity_id, const float x, const float y) = 0;
        virtual void move_entity(const EntityId& entity_id, const Point<float>& location) = 0;
        virtual void destroy_entity(const EntityId& entity_id) = 0;
        virtual void add_game_view(IGameViewPtr view, EntityId entity_id=INVALID_ENTITY_ID) = 0;
        virtual void remove_game_view(IGameViewPtr) = 0;
        virtual WeakEntityPtr get_entity(const EntityId& entity_id) = 0;
        virtual EntityPtr create_entity() = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IGameLogic() {}
    };
}
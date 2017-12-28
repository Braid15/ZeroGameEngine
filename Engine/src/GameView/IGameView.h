#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Entity/Entity.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    typedef uint32 GameViewId;
    extern const GameViewId INVALID_GAME_VIEW_ID;

    enum class GameViewType {
        human,
        ai,
        remote,
        recorder,
        other
    };

    class IGameView : public IZeroObject {
    public:
        virtual bool restore() = 0;
        virtual bool lost_device() = 0;
        virtual void initialize() = 0;
        virtual bool render(Tick delta_time) = 0;
        virtual void update(Tick delta_time) = 0;
        virtual const GameViewId& get_id() const = 0;
        virtual const GameViewType& get_type() const = 0;
        virtual void attach(GameViewId view_id, EntityId entity_id) = 0;
        virtual bool msg_proc(AppMsg::ptr ) = 0;
        virtual ~IGameView() {}
        virtual StringRepr to_string() const = 0;
    };

    typedef std::shared_ptr<IGameView> IGameViewPtr;
    typedef std::list<IGameViewPtr> GameViewList;
}
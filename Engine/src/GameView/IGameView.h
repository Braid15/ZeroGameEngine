#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Entity/Entity.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    typedef uint32_t GameViewId;
    extern const GameViewId INVALID_GAME_VIEW_ID = 0;

    enum class GameViewType {
        human,
        ai,
        remote,
        recorder,
        other
    };

    class IGameView : public IZeroObject {
    public:
        virtual bool on_restore() = 0;
        virtual bool on_lost_device() = 0;
        virtual bool on_render(Ticks delta_time) = 0;
        virtual void on_update(Ticks delta_time) = 0;
        virtual const GameViewId& get_id() const = 0;
        virtual const GameViewType& get_type() const = 0;
        virtual void on_attach(GameViewId view_id, EntityId entity_id) = 0;
        virtual bool on_msg_proc(const AppMsg* const app_msg) = 0;
        virtual ~IGameView() {}
        virtual StringRepr to_string() const = 0;
    };

    typedef std::list<std::shared_ptr<IGameView>> GameViewList;
}
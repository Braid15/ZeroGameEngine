#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    class IScreenElement : public IZeroObject {
    public:
        virtual bool on_restore() = 0;
        virtual bool on_lost_device() = 0;
        virtual bool on_render(Ticks delta_time) = 0;
        virtual void on_update(Ticks delta_time) = 0;
        virtual int get_z_order() const = 0;
        virtual void set_z_order(int const z_order) = 0;
        virtual bool is_visible() const = 0;
        virtual void set_visible(bool visible) = 0;
        virtual void on_msg_proc(const AppMsg* const app_msg) = 0;
        virtual ~IScreenElement() {}
        virtual bool const operator <(const IScreenElement& other) { return get_z_order() < other.get_z_order(); }
        virtual bool const operator <=(const IScreenElement& other) { return get_z_order() <= other.get_z_order(); }
        virtual bool const operator >(const IScreenElement& other) { return get_z_order() > other.get_z_order(); }
        virtual bool const operator >=(const IScreenElement& other) { return get_z_order() >= other.get_z_order(); }
        virtual bool const operator ==(const IScreenElement& other) { return get_z_order() == other.get_z_order(); }
        virtual StringRepr to_string() const = 0;
    };

    typedef std::list<std::shared_ptr<IScreenElement>> ScreenElementList;
}
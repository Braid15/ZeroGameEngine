#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    class IScreenElement : public IZeroObject {
    public:
        virtual bool restore() = 0;
        virtual bool lost_device() = 0;
        virtual bool render(Tick delta_time) = 0;
        virtual void update(Tick delta_time) = 0;
        virtual int get_z_order() const = 0;
        virtual void set_z_order(int const z_order) = 0;
        virtual bool is_visible() const = 0;
        virtual void set_visible(bool visible) = 0;
        virtual bool on_msg_proc(const AppMsg* const app_msg) = 0;
        virtual ~IScreenElement() {}
        virtual bool const operator <(const IScreenElement& other) { return get_z_order() < other.get_z_order(); }
        virtual bool const operator <=(const IScreenElement& other) { return get_z_order() <= other.get_z_order(); }
        virtual bool const operator >(const IScreenElement& other) { return get_z_order() > other.get_z_order(); }
        virtual bool const operator >=(const IScreenElement& other) { return get_z_order() >= other.get_z_order(); }
        virtual bool const operator ==(const IScreenElement& other) { return get_z_order() == other.get_z_order(); }
        virtual StringRepr to_string() const = 0;

        typedef std::shared_ptr<IScreenElement> ptr;

        struct sort_by_z_order_predicate {
            bool operator()(const IScreenElement::ptr& lhs, const IScreenElement::ptr& rhs) const {
                return *lhs < *rhs;
            }
        };
    };

    typedef std::list<IScreenElement::ptr> ScreenElementList;
}
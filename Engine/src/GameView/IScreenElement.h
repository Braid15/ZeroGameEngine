#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    typedef uint32_t ScreenElementId;

    extern const ScreenElementId INVALID_SCREEN_ELEMENT_ID;

    class IScreenElement {
    public:
        virtual bool restore() = 0;
        virtual bool lost_device() = 0;
        virtual bool render(Tick delta_time) = 0;
        virtual void update(Tick delta_time) = 0;
        virtual uint32_t get_z_order() const = 0;
        virtual void set_z_order(uint32_t const z_order) = 0;
        virtual bool is_visible() const = 0;
        virtual void set_visible(bool visible) = 0;
        virtual bool on_msg_proc(AppMsg::ptr app_msg) = 0;
        virtual ScreenElementId get_id() const = 0;
        virtual ~IScreenElement() {}
        virtual bool const operator <(const IScreenElement& other) { return get_z_order() < other.get_z_order(); }
        virtual bool const operator <=(const IScreenElement& other) { return get_z_order() <= other.get_z_order(); }
        virtual bool const operator >(const IScreenElement& other) { return get_z_order() > other.get_z_order(); }
        virtual bool const operator >=(const IScreenElement& other) { return get_z_order() >= other.get_z_order(); }
        virtual bool const operator ==(const IScreenElement& other) { return get_z_order() == other.get_z_order(); }

        typedef std::shared_ptr<IScreenElement> ptr;

        struct sort_by_z_order_predicate {
            bool operator()(const IScreenElement::ptr& lhs, const IScreenElement::ptr& rhs) const {
                return *lhs < *rhs;
            }
        };
    };

    typedef std::list<IScreenElement::ptr> ScreenElementList;

    class BaseScreenElement : public IScreenElement, public IZeroObject {
    private:
        int32_t _z_order;
        bool _is_visible;
        ScreenElementId _id;
    public:
        virtual StringRepr to_string() const = 0;

        BaseScreenElement();
        inline virtual ~BaseScreenElement() {}
        inline virtual bool restore() override { return true; }
        inline virtual bool lost_device() override { return true; }
        inline virtual bool render(Tick delta_time) override { return true; }
        inline virtual void update(Tick delta_time) override {}
        inline virtual bool on_msg_proc(AppMsg::ptr msg) override { return false; }
        inline uint32_t get_z_order() const override { return _z_order; }
        inline void set_z_order(uint32_t const z_order) override { _z_order = z_order; }
        inline bool is_visible() const override { return _is_visible; }
        inline void set_visible(bool visible) override { _is_visible = visible; }
        inline ScreenElementId get_id() const override { return _id; }
        typedef std::shared_ptr<BaseScreenElement> ptr;
    };
}
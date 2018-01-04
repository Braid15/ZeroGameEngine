#pragma once

#include "../ZeroEngineStd.h"
#include "EventType.h"
#include "EventData.h"
#include "EventListener.h"
#include "../AppLayer/Game.h"

namespace ZeroEngine {

    // -------------------
    // Convienience macros
    // -------------------

    #define Q(x) #x
    #define QUOTE(x) Q(x)

    // @NOTE: This does not declare a static create method
    // since it doesn't know the parameters.
    #define DECLARE_EVENT_METHODS(class_name)                                       \
    public:                                                                         \
        typedef std::shared_ptr<class_name> s_ptr;                                  \
        static const EventType type;                                                \
        IEventDataPtr copy() const override;                                        \
        inline const EventType& get_event_type() const override { return type; }    \
        inline StringRepr to_string() const override { return QUOTE(class_name); }  \
        static class_name::s_ptr cast(IEventDataPtr);                               \
    private:                                                                        \
        class_name(const class_name&);                                              \
        

    // @NOTE: This does not define copy ctor.
    #define DEFINE_EVENT_METHODS(class_name)                          \
    const EventType class_name::type = STRING_ID(QUOTE(class_name));  \
                                                                      \
    IEventDataPtr class_name::copy() const {                          \
        return IEventDataPtr(zero_new class_name(*this));             \
    }                                                                 \
                                                                      \
    class_name::s_ptr class_name::cast(IEventDataPtr data_ptr) {      \
        assert(data_ptr->is_type(type));                              \
        return std::static_pointer_cast<class_name>(data_ptr);        \
    }
    
        
        
    // Use copy ctor to handle static event copy methods


    #define REGISTER_EVENT_LISTENER(delegate, type) \
        ZeroEventManager::register_listener(fastdelegate::MakeDelegate(this, (delegate)), (type));

    #define UNREGISTER_EVENT_LISTENER(delegate, type) \
        ZeroEventManager::unregister_listener(fastdelegate::MakeDelegate(this, (delegate)), (type));

    #define REGISTER_EVENT_DELEGATE(class_name, event_type) \
        ZeroEventManager::register_listener(           \
            fastdelegate::MakeDelegate(this, &class_name::event_type##_delegate), \
            event_type::type);

    #define UNREGISTER_EVENT_DELEGATE(class_name, event_type) \
        ZeroEventManager::unregister_listener( \
            fastdelegate::MakeDelegate(this, &class_name::event_type##_delegate), \
            event_type::type);

    #define DECLARE_EVENT_DELEGATE_SIG(event_name, var_name) void event_name##_delegate(IEventDataPtr var_name)

    #define DEFINE_EVENT_DELEGATE_SIG(class_name, event_name, var_name) void class_name::event_name##_delegate(IEventDataPtr var_name)


    // -------------
    // IEventManager
    // -------------

    const Uint32 MAX_MILLISECONDS = 0xffffffff;

    class IEventManager {
    public:
        virtual bool register_listener(const EventListenerDelegate& delegate, const EventType& type) = 0;
        virtual bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type) = 0;
        virtual bool trigger_event(const IEventDataPtr& event_data) const = 0;
        virtual bool queue_event(const IEventDataPtr& event_data) = 0;
        virtual bool abort_event(const EventType& type, bool all=false) = 0;
        virtual bool update(Uint32 max_milliseconds=MAX_MILLISECONDS) = 0;
        virtual const char* get_name() const = 0;
    };

    // ----------------
    // BaseEventManager
    // ----------------

    // @TODO: Move to seperate file

    const Uint8 EVENT_MANAGER_QUEUE_COUNT = 2;

    class BaseEventManager : public IEventManager, public IZeroObject {
    private:
        typedef std::list<EventListenerDelegate> EventListenerList;
        typedef std::map<EventType, EventListenerList> EventListenerMap;
        typedef std::list<IEventDataPtr> EventQueue;
    private:
        const char* _name;
        EventListenerMap _listener_map;
        EventQueue _event_queues[EVENT_MANAGER_QUEUE_COUNT];
        Int8 _active_queue;
    public:
        virtual bool register_listener(const EventListenerDelegate& delegate, const EventType& type) override;
        virtual bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type) override;
        virtual bool trigger_event(const IEventDataPtr& event_data) const override;
        virtual bool abort_event(const EventType& type, bool all=false) override;
        virtual bool queue_event(const IEventDataPtr& event_data) override;
        virtual bool update(Uint32 max_milliseconds=MAX_MILLISECONDS) override;
        inline virtual ~BaseEventManager() {}
        inline virtual StringRepr to_string() const override { return _name; }
        inline const char* get_name() const override { return _name; }
    protected:
        explicit BaseEventManager(const char* name);
    };

    // ----------------
    // ZeroEventManager
    // ----------------

    // Make singleton?

    // @TODO: Move to seperate file

    class ZeroEventManager final : public BaseEventManager {
    private:
        inline ZeroEventManager() : BaseEventManager("ZeroEventManager") {};
        static BaseEventManager* _event_manager;
    public:
        static void initialize();
        static bool register_listener(const EventListenerDelegate& delegate, const EventType& type);
        static bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type);
        static bool trigger_event(const IEventDataPtr& event_data);
        static bool abort_event(const EventType& type, bool all=false);
        static bool queue_event(const IEventDataPtr& event_data);
        static bool update(Uint32 max_milliseconds=MAX_MILLISECONDS);
        static const char* get_name();
        static StringRepr to_string();
        static void shutdown();
        ~ZeroEventManager();
    };

}
#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Utils/MemoryPool.h"
#include "AppMsgType.h"
#include "AppMsgArgs.h"

// @@TODO: AppMsg needs to take on the responsibliy of deleting instances
// insteade of AppMsgFactory and AppMsg needs to make it so only AppMsgFactory can
// create instances.
// @@TODO: Copyctors for AppMs

namespace ZeroEngine {

    class AppMsg;
    typedef AppMsg* AppMsgPtr;

    class AppMsg : public IZeroObject {
    private:
        static MemoryPool* _memory_pool;
        AppMsgArgsPtr _args;
#ifdef _DEBUG
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
#endif
    public:
        virtual AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        inline Time get_creation_time() { return _args->get_creation_time(); }
    protected:
        AppMsg(AppMsgArgsPtr);
        virtual ~AppMsg();
        inline AppMsgArgs& get_args() { return *_args; }
        inline void set_args(AppMsgArgsPtr args) { _args = args; }
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
        static void init_memory_pool();
        static void destroy_memory_pool();
        friend class AppMsgFactory;
    };

    class NullMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline StringRepr to_string() const { return "NullMsg"; }
        inline AppMsgType get_type() const { return type; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        inline NullMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~NullMsg() {}
    };


    class MouseMotionMsg : public AppMsg {
    private:
        MouseMotionMsgArgs* _mouse_args;
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "MouseMotionMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        MouseMotionMsg(AppMsgArgsPtr args);
        inline ~MouseMotionMsg() {}
    };

    class QuitMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "QuitMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        inline QuitMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~QuitMsg() {}
    };

    class UnhandledMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "UnhandledMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr arg);
    protected:
        inline UnhandledMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~UnhandledMsg() {}

    };

    class WindowMsg : public AppMsg {
    private:
        WindowMsgArgs* _window_msg_args;
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "WindowMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        WindowMsg(AppMsgArgsPtr args);
        inline ~WindowMsg() {}
    };
}
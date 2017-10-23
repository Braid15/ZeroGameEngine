#pragma once

#include "IZeroObject.h"
#include "Time.h"

namespace ZeroEngine {

    enum AppMsgType {
        NULL_MSG,
        QUIT_MSG,
        KEYDOWN_MSG,
        KEYUP_MSG,
        KEYBOARD_MSG,
        MOUSE_MSG,
        MOUSE_MOVE_MSG,
        MOUSE_BUTTON_DOWN_MSG,
        MOUSE_BUTTON_UP_MSG,
    };

    class AppMsgArgs : public IZeroObject {
    public:
        static AppMsgArgs empty;
        inline virtual ~AppMsgArgs() {}

    /* IZeroObject */
    public:
        inline virtual StringRepr to_string() const { return "AppMsgArgs"; }

    protected:
        inline AppMsgArgs() {}
    };



    class EmptyMsgArgs : public AppMsgArgs {
    public:
        inline EmptyMsgArgs() : AppMsgArgs() {}
        inline ~EmptyMsgArgs() {}

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };



    class AppMsg : public IZeroObject {
    public:
        inline AppMsg( Time time ): 
            _creation_time( time ),
            _args( AppMsgArgs::empty ) 
        {}
        inline virtual ~AppMsg() {}
        inline Time get_creation_time() { return _creation_time; }
        inline virtual AppMsgType get_type() const { return NULL_MSG; }

    /* IZeroObject */
    public:
        inline virtual StringRepr to_string() const override { return "NullMsg"; }

    protected:
        inline AppMsgArgs get_args() { return _args; }

    private:
        AppMsgArgs _args;
        Time _creation_time;
    };

    // So I can switch to shared_ptr at somepoint
    typedef AppMsg* AppMsgPtr;


    class MouseMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline MouseMsg( Time time ) : AppMsg( time ) {}

    /* AppMsg */
    public:
        inline AppMsgType get_type() const override { return MOUSE_MSG; }

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "MouseMsg"; }
    };



    class QuitMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline QuitMsg( Time time ) : AppMsg( time ) {}

    /* AppMsg */
    public:
        inline AppMsgType get_type() const override { return QUIT_MSG; }

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "QuitMsg"; }
    };





}
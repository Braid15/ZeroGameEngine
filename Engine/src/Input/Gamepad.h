#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef std::string GamepadTriggerName;
    typedef std::string GamepadButtonName;
    typedef std::string GamepadDirectionalName;
    typedef std::string GamepadJoystickName;

    class IGamepadHandler : public IZeroObject {
    public:
        virtual bool on_trigger(const GamepadTriggerName& trigger_name, const Float32 pressure) = 0;
        virtual bool on_button_up(const GamepadButtonName& button_name) = 0;
        virtual bool on_button_down(const GamepadButtonName& button_name, const Float32 pressure) = 0;
        virtual bool on_directional_pad(const GamepadDirectionalName& directional_name) = 0;
        virtual bool on_joystick_move(const GamepadJoystickName& joystick_name, const Float32 x, const Float32 y) = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IGamepadHandler() {}
    };
}
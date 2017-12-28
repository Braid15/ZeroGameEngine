#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef std::string JoystickButton;

    class IJoystickHandler : public IZeroObject {
    public:
        virtual bool on_button_down(const JoystickButton& button, const float32 pressure) = 0;
        virtual bool on_button_up(const JoystickButton& button) = 0;
        virtual bool on_joystick_move(const float32 x, const float32 y) = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IJoystickHandler() {}
    };
}
#pragma once

#include "../ZeroEngineStd.h"
#include "../AppMsg/AppMsg.h"

// @TEMP: Until I move the necessary things to a different file

namespace ZeroEngine {
    
    // This class has a similar responsiblity to Keyboard class
    class Mouse {
    private:
        static std::array<ButtonState, static_cast<int>(MouseButton::end)> _button_states;
        static Point<int32_t> _pointer_position;
        static MouseWheelDirection _wheel_direction;
    public:
        static bool is_pressed(const MouseButton& button);
        static const Point<int32_t>& position();
        // @TODO: This isn't working properly yet
        // static const MouseWheelDirection& wheel_direction();

        // @TEMP:
        static void set(const MouseMotionMsg* const);
        static void set(const MouseButtonMsg* const);
        static void set(const MouseWheelMsg* const);
    private:
        inline Mouse() {}
        inline Mouse(const Mouse&) {}
        inline ~Mouse() {}
    };
}
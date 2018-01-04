#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"
#include "../AppMsg/AppMsg.h"

// @TEMP: Until I move the necessary things to a different file

namespace ZeroEngine {
    
    class IMouseHandler {
    public:
        virtual bool on_mouse_move(const Point<Int32> pos, const Int32 radius) = 0;
        virtual bool on_button_down(const Point<Int32> pos, const Int32 radius, const MouseButton& button) = 0;
        virtual bool on_button_up(const Point<Int32> pos, const Int32 radius, const MouseButton& button) = 0;
        virtual ~IMouseHandler() {}
    };

    class NullMouseHandler : public IZeroObject, public IMouseHandler {
    public:
        inline NullMouseHandler() {}
        inline ~NullMouseHandler() {}
        inline bool on_mouse_move(const Point<Int32> pos, const Int32 radius) override { return false; }
        inline bool on_button_down(const Point<Int32> pos, const Int32 radius, const MouseButton& button)
            override { return false; }
        inline bool on_button_up(const Point<Int32> pos, const Int32 radius, const MouseButton& button)
            override { return false; }
        inline StringRepr to_string() const override { return "NullMouseHandler"; }
    };


    // This class has a similar responsiblity to Keyboard class
    class Mouse {
    private:
        static std::array<ButtonState, static_cast<Int32>(MouseButton::end)> _button_states;
        static Point<Int32> _pointer_position;
        static MouseWheelDirection _wheel_direction;
    public:
        static bool is_pressed(const MouseButton& button);
        static const Point<Int32>& position();
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
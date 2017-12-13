#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"
#include "../AppMsg/AppMsg.h"

// @TEMP: Until I move the necessary things to a different file

namespace ZeroEngine {
    
    class IMouseHandler : public IZeroObject {
        virtual bool on_mouse_move(const int x, const int y, const int radius) = 0;
        virtual bool on_mouse_move(const float x, const float y, const int radius) = 0;
        virtual bool on_mouse_move(const Point<float>& pos, const int radius) = 0;
        virtual bool on_mouse_move(const Point<int>& pos, const int radius) = 0;
        virtual bool on_button_down(const int x, const int y, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_down(const float x, const float y, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_down(const Point<float>& pos, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_down(const Point<int>& pos, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_up(const int x, const int y, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_up(const float x, const float y, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_up(const Point<float>& pos, const int radius, const MouseButton& button) = 0;
        virtual bool on_button_up(const Point<int>& pos, const int radius, const MouseButton& button) = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IMouseHandler() {}
    };


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
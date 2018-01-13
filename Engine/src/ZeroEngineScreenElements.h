#pragma once 

#include "ZeroEngineStd.h"
#include "AppLayer/Game.h"
#include "GameView/IScreenElement.h"
#include "Graphics/Graphics.h"

namespace ZeroEngine {

    class LineScreenElement : public BaseScreenElement {
    private:
        Point<Int32> _from;
        Point<Int32> _to;
        Color _color;
    public:
        inline LineScreenElement(Point<Int32> from, Point<Int32> to, Color color)
            : _from(from), _to(to), _color(color) {
        }
        inline StringRepr to_string() const { return "LineScreenElement"; }

        inline bool render(Tick delta_time) override {
            Game::get_renderer()->draw_line(_from, _to, _color);
            return true;
        }
    };
}
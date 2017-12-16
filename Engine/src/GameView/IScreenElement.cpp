#include "IScreenElement.h"

namespace ZeroEngine {

    const ScreenElementId INVALID_SCREEN_ELEMENT_ID = 0;

    static ScreenElementId screen_element_count = INVALID_SCREEN_ELEMENT_ID;

    BaseScreenElement::BaseScreenElement() {
        _z_order = 0;
        _is_visible = true;
        _id = ++screen_element_count;
    }
}
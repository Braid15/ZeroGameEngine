#include "SdlMsgTranslator.h"

namespace ZeroEngine {

    static Key sdl_keysym_to_keycode_conversion(SDL_Keysym);

    const AppMsg* const SdlMsgTranslator::get_translated_message() {
        Uint32 time = _sdl_event.common.timestamp;
        switch (_sdl_event.type) {
            case SDL_QUIT:
                return _factory->create_message(AppMsgType::quit, zero_new EmptyMsgArgs(time));
            case SDL_APP_TERMINATING:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_LOWMEMORY:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_WILLENTERBACKGROUND:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_DIDENTERBACKGROUND:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_WILLENTERFOREGROUND:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_DIDENTERFOREGROUND:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_WINDOWEVENT:

                //_sdl_event.window.event;
                //_sdl_event.window.data1;
                //_sdl_event.window.data2;

                return _factory->create_message(AppMsgType::window, zero_new WindowMsgArgs(time));
            case SDL_SYSWMEVENT:
                return _factory->create_message(AppMsgType::system, zero_new SystemMsgArgs(time));

            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                Uint16 mod_state = _sdl_event.key.keysym.mod;
                KeyModStateArray keymod_states = { KeyState::null };
                keymod_states[static_cast<Int32>(KeyMod::left_shift)] = (mod_state == KMOD_LSHIFT || mod_state == KMOD_SHIFT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::right_shift)] = (mod_state == KMOD_RSHIFT || mod_state == KMOD_SHIFT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::left_alt)] = (mod_state == KMOD_LALT || mod_state == KMOD_ALT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::right_alt)] = (mod_state == KMOD_RALT || mod_state == KMOD_ALT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::left_control)] = (mod_state == KMOD_LCTRL || mod_state == KMOD_CTRL) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::right_control)] = (mod_state == KMOD_RCTRL || mod_state == KMOD_CTRL) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<Int32>(KeyMod::caps_lock)] = (mod_state == KMOD_CAPS) ? KeyState::pressed : KeyState::released;

                KeyState state = _sdl_event.key.state == 1 ? KeyState::pressed : KeyState::released;
                Key key = sdl_keysym_to_keycode_conversion(_sdl_event.key.keysym);

                Uint32 window = _sdl_event.key.windowID;
                bool repeat = _sdl_event.key.repeat == 1;

                KeyboardMsgArgs* args = zero_new KeyboardMsgArgs(time, window, key, repeat, state, keymod_states);

                return _factory->create_message(AppMsgType::keyboard, args);
                /*
                if (_sdl_event.type == SDL_KEYDOWN) {
                    return _factory->create_message(AppMsg::keydown, args);
                } else {
                    return _factory->create_message(AppMsg::keyup, args);
                }
                */
            }
            case SDL_TEXTEDITING:
                return _factory->create_message(AppMsgType::text_edit, zero_new TextEditMsgArgs(time));
            case SDL_TEXTINPUT:
                return _factory->create_message(AppMsgType::text_input, zero_new TextInputMsgArgs(time));
            case SDL_KEYMAPCHANGED:
                return _factory->create_message(AppMsgType::keymap_changed, zero_new KeyMapChangedMsgArgs(time));
            case SDL_MOUSEMOTION:
            {

                Uint32 state = _sdl_event.motion.state;
                Uint32 mouse = _sdl_event.motion.which;
                Uint32 window = _sdl_event.motion.windowID;
                Int32 x_pos = _sdl_event.motion.x;
                Int32 y_pos = _sdl_event.motion.y;
                Int32 y_rel = _sdl_event.motion.yrel;
                Int32 x_rel = _sdl_event.motion.xrel;

                // SDL_MouseMotionEvent.state returns a bitmask of the current state of the mouse.
                // Perform bitwise & to check if a button is pressed.
                // This is equivilant of calling SDL_GetMouseState() & SDL_BUTTON(<button_number>)

                MouseButtonStateArray button_states;

                Int32 left_button = static_cast<Int32>(MouseButton::left);
                button_states[left_button] = (state & 1 << (left_button - 1)) ? ButtonState::pressed : ButtonState::released;

                Int32 middle_button = static_cast<Int32>(MouseButton::middle);
                button_states[middle_button] = (state & 1 << (middle_button - 1)) ? ButtonState::pressed : ButtonState::released;

                Int32 right_button = static_cast<Int32>(MouseButton::right);
                button_states[right_button] = (state & 1 << (right_button - 1)) ? ButtonState::pressed : ButtonState::released;

                Int32 button_four = static_cast<Int32>(MouseButton::four);
                button_states[button_four] = (state & 1 << (button_four - 1)) ? ButtonState::pressed : ButtonState::released;

                Int32 button_five = static_cast<Int32>(MouseButton::five);
                button_states[button_five] = (state & 1 << (button_five - 1)) ? ButtonState::pressed : ButtonState::released;

                MouseMotionMsgArgs* args = 
                    zero_new MouseMotionMsgArgs(time, window, mouse, button_states, x_pos, y_pos, x_rel, y_rel);

                return _factory->create_message(AppMsgType::mouse_motion, args);
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                Uint32 window = _sdl_event.button.windowID;
                Uint32 which = _sdl_event.button.which;
                ButtonState state = (_sdl_event.type == SDL_MOUSEBUTTONDOWN) ? ButtonState::pressed : ButtonState::released;
                Uint8 clicks = _sdl_event.button.clicks;

                MouseButton button = MouseButton::null;

                if (_sdl_event.button.button == 1) {
                    button = MouseButton::left; 
                } else if (_sdl_event.button.button == 2) {
                    button = MouseButton::middle;
                } else if (_sdl_event.button.button == 3) {
                    button = MouseButton::right;
                } else if (_sdl_event.button.button == 4) {
                    button = MouseButton::four;
                } else if (_sdl_event.button.button == 5) {
                    button = MouseButton::five;
                }

                Int32 x = _sdl_event.button.x;
                Int32 y = _sdl_event.button.y;

                MouseButtonMsgArgs* args = 
                    zero_new MouseButtonMsgArgs(time, window, which, state, clicks, button, x, y);

                return _factory->create_message(AppMsgType::mouse_button, args);
                /*
                if (_sdl_event.type == SDL_MOUSEBUTTONDOWN) {
                    return _factory->create_message(AppMsg::mouse_button_down, args);
                } else {
                    return _factory->create_message(AppMsg::mouse_button_up, args);
                }
                */
            }

            // @TODO: Doesn't handle scrolling along x axis
            case SDL_MOUSEWHEEL:
            {
                Uint32 mouse = _sdl_event.wheel.which;
                Uint32 window = _sdl_event.wheel.windowID;
                Int32 x = _sdl_event.wheel.x;
                Int32 y = _sdl_event.wheel.y;

                // So the values are never flipped
                if (_sdl_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                    x *= -1;
                    y *= -1;
                }

                MouseWheelDirection direction = (y > 0) ? MouseWheelDirection::up : MouseWheelDirection::down;

                MouseWheelMsgArgs* args = zero_new MouseWheelMsgArgs(time, window, mouse, x, y, direction);

                return _factory->create_message(AppMsgType::mouse_wheel, args);
            }

            case SDL_JOYAXISMOTION:
                return _factory->create_message(AppMsgType::joy_axis_motion, zero_new JoyAxisMotionMsgArgs(time));
            case SDL_JOYBALLMOTION:
                return _factory->create_message(AppMsgType::joy_ball_motion, zero_new JoyBallMotionMsgArgs(time));
            case SDL_JOYHATMOTION:
                return _factory->create_message(AppMsgType::joy_hat_motion, zero_new JoyHatMotionMsgArgs(time));
            case SDL_JOYBUTTONDOWN:
                return _factory->create_message(AppMsgType::joy_button_down, zero_new JoyButtonMsgArgs(time));
            case SDL_JOYBUTTONUP:
                return _factory->create_message(AppMsgType::joy_button_up, zero_new JoyButtonMsgArgs(time));
            case SDL_JOYDEVICEADDED:
                return _factory->create_message(AppMsgType::joy_device_added, zero_new JoyDeviceAddedMsgArgs(time));
            case SDL_JOYDEVICEREMOVED:
                return _factory->create_message(AppMsgType::joy_device_removed, zero_new JoyDeviceRemovedMsgArgs(time));
            case SDL_CONTROLLERAXISMOTION:
                return _factory->create_message(AppMsgType::controller_axis_motion, zero_new ControllerAxisMotionMsgArgs(time));
            case SDL_CONTROLLERBUTTONDOWN:
                return _factory->create_message(AppMsgType::controller_button_down, zero_new ControllerButtonMsgArgs(time));
            case SDL_CONTROLLERBUTTONUP:
                return _factory->create_message(AppMsgType::controller_button_up, zero_new ControllerButtonMsgArgs(time));
            case SDL_CONTROLLERDEVICEADDED:
                return _factory->create_message(AppMsgType::controller_device_added, zero_new ControllerDeviceAddedMsgArgs(time));
            case SDL_CONTROLLERDEVICEREMOVED:
                return _factory->create_message(AppMsgType::controller_device_removed, zero_new ControllerDeviceRemovedMsgArgs(time));
            case SDL_CONTROLLERDEVICEREMAPPED:
                return _factory->create_message(AppMsgType::controller_device_remapped, zero_new ControllerDeviceRemappedMsgArgs(time));
            case SDL_FINGERUP:
                return _factory->create_message(AppMsgType::finger_up, zero_new FingerUpMsgArgs(time));
            case SDL_FINGERDOWN:
                return _factory->create_message(AppMsgType::finger_down, zero_new FingerDownMsgArgs(time));
            case SDL_FINGERMOTION:
                return _factory->create_message(AppMsgType::finger_motion, zero_new FingerMotionMsgArgs(time));
            case SDL_DOLLARGESTURE:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_DOLLARRECORD:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_MULTIGESTURE:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_CLIPBOARDUPDATE:
                return _factory->create_message(AppMsgType::clipboard, zero_new ClipboardMsgArgs(time));
            case SDL_DROPFILE:
                return _factory->create_message(AppMsgType::drop_file, zero_new DropFileMsgArgs(time));
            case SDL_DROPTEXT:
                return _factory->create_message(AppMsgType::drop_text, zero_new DropTextMsgArgs(time));
            case SDL_DROPBEGIN:
                return _factory->create_message(AppMsgType::drop_begin, zero_new DropBeginMsgArgs(time));
            case SDL_DROPCOMPLETE:
                return _factory->create_message(AppMsgType::drop_complete, zero_new DropCompleteMsgArgs(time));
            case SDL_AUDIODEVICEADDED:
                return _factory->create_message(AppMsgType::audio_device_added, zero_new AudioDeviceAddedMsgArgs(time));
            case SDL_AUDIODEVICEREMOVED:
                return _factory->create_message(AppMsgType::audio_device_removed, zero_new AudioDeviceRemovedMsgArgs(time));
            case SDL_RENDER_TARGETS_RESET:
                return _factory->create_message(AppMsgType::render_targets_reset, zero_new RenderTargetsResetMsgArgs(time));
            case SDL_RENDER_DEVICE_RESET:
                return _factory->create_message(AppMsgType::render_device_reset, zero_new RenderDeviceResetMsgArgs(time));
            case SDL_USEREVENT:
                return _factory->create_message(AppMsgType::unhandled, zero_new EmptyMsgArgs(time));
            default:
                // This should never be reached, but just in case
                return _factory->create_message(AppMsgType::null, zero_new EmptyMsgArgs(time));
        }
    }

    void SdlMsgTranslator::set_sdl_event_to_translate(const SDL_Event& event) {
        _sdl_event = event;
    }

    Key sdl_keysym_to_keycode_conversion(SDL_Keysym keysym) {
        switch (keysym.sym) {
            case SDLK_0:
                return Key::zero;
            case SDLK_1:
                return Key::one;
            case SDLK_2:
                return Key::two;
            case SDLK_3:
                return Key::three;
            case SDLK_4:
                return Key::four;
            case SDLK_5:
                return Key::five;
            case SDLK_6:
                return Key::six;
            case SDLK_7:
                return Key::seven;
            case SDLK_8:
                return Key::eight;
            case SDLK_9:
                return Key::nine;
            case SDLK_a:
                return Key::a;
            case SDLK_b:
                return Key::b;
            case SDLK_c:
                return Key::c;
            case SDLK_d:
                return Key::d;
            case SDLK_e:
                return Key::e;
            case SDLK_f:
                return Key::f;
            case SDLK_g:
                return Key::g;
            case SDLK_h:
                return Key::h;
            case SDLK_i:
                return Key::i;
            case SDLK_j:
                return Key::j;
            case SDLK_k:
                return Key::k;
            case SDLK_l:
                return Key::l;
            case SDLK_m:
                return Key::m;
            case SDLK_n:
                return Key::n;
            case SDLK_o:
                return Key::o;
            case SDLK_p:
                return Key::p;
            case SDLK_q:
                return Key::q;
            case SDLK_r:
                return Key::r;
            case SDLK_s:
                return Key::s;
            case SDLK_t:
                return Key::t;
            case SDLK_u:
                return Key::u;
            case SDLK_v:
                return Key::v;
            case SDLK_w:
                return Key::w;
            case SDLK_x:
                return Key::x;
            case SDLK_y:
                return Key::y;
            case SDLK_z:
                return Key::z;
            case SDLK_UP:
                return Key::up;
            case SDLK_RIGHT:
                return Key::right;
            case SDLK_DOWN:
                return Key::down;
            case SDLK_LEFT:
                return Key::left;
            case SDLK_ESCAPE:
                return Key::escape;
            case SDLK_BACKSPACE:
                return Key::backspace;
            case SDLK_RETURN:
                return Key::enter;
            case SDLK_LCTRL:
                return Key::left_control;
            case SDLK_RCTRL:
                return Key::right_control;
            case SDLK_LALT:
                return Key::left_alt;
            case SDLK_RALT:
                return Key::right_alt;
            case SDLK_LSHIFT:
                return Key::left_shift;
            case SDLK_RSHIFT:
                return Key::right_shift;
            case SDLK_TAB:
                return Key::tab;
            case SDLK_DELETE:
                return Key::del;
            case SDLK_SPACE:
                return Key::space;
            case SDLK_AMPERSAND:
                return Key::ampersand;
            case SDLK_ASTERISK:
                return Key::asterisk;
            case SDLK_AT:
                return Key::at;
            case SDLK_CARET:
                return Key::caret;
            case SDLK_COLON:
                return Key::colon;
            case SDLK_DOLLAR:
                return Key::dollar;
            case SDLK_EXCLAIM:
                return Key::exclamation;
            case SDLK_GREATER:
                return Key::greater_than;
            case SDLK_HASH:
                return Key::hash;
            case SDLK_LEFTPAREN:
                return Key::left_paren;
            case SDLK_RIGHTPAREN:
                return Key::right_paren;
            case SDLK_LESS:
                return Key::less_than;
            case SDLK_PERCENT:
                return Key::percent;
            case SDLK_PLUS:
                return Key::plus;
            case SDLK_QUESTION:
                return Key::question_mark;
            case SDLK_QUOTEDBL:
                return Key::double_quote;
            case SDLK_UNDERSCORE:
                return Key::underscore;
            case SDLK_SLASH:
                return Key::forward_slash;
            case SDLK_BACKSLASH:
                return Key::back_slash;
            case SDLK_SEMICOLON:
                return Key::semicolon;
            case SDLK_RIGHTBRACKET:
                return Key::right_bracket;
            case SDLK_PERIOD:
                return Key::period;
            case SDLK_MINUS:
                return Key::minus;
            case SDLK_LEFTBRACKET:
                return Key::left_bracket;
            case SDLK_EQUALS:
                return Key::equal;
            case SDLK_COMMA:
                return Key::comma;
            case SDLK_QUOTE:
                return Key::single_quote;
            case SDLK_BACKQUOTE:
                return Key::tilda;
            case SDLK_PAGEDOWN:
                return Key::page_down;
            case SDLK_PAGEUP:
                return Key::page_up;
            case SDLK_CAPSLOCK:
                return Key::caps_lock;
            default:
                return Key::null;
        }
    }
}

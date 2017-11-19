#include "SdlMsgTranslator.h"

namespace ZeroEngine {

    static KeyCode sdl_keysym_to_keycode_conversion(SDL_Keysym);

    const AppMsg* const SdlMsgTranslator::get_translated_message() {
        uint32_t time = _sdl_event.common.timestamp;
        switch (_sdl_event.type) {
            case SDL_QUIT:
                return _factory->create_message(AppMsg::quit, zero_new EmptyMsgArgs(time));
            case SDL_APP_TERMINATING:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_LOWMEMORY:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_WILLENTERBACKGROUND:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_DIDENTERBACKGROUND:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_WILLENTERFOREGROUND:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_APP_DIDENTERFOREGROUND:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_WINDOWEVENT:

                //_sdl_event.window.event;
                //_sdl_event.window.data1;
                //_sdl_event.window.data2;

                return _factory->create_message(AppMsg::window, zero_new WindowMsgArgs(time));
            case SDL_SYSWMEVENT:
                return _factory->create_message(AppMsg::system, zero_new SystemMsgArgs(time));

            // @TODO: FInish implementing KeydownMsg and KeyupMsg
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                uint16_t mod_state = _sdl_event.key.keysym.mod;
                KeyModStateArray keymod_states = { KeyState::null };
                keymod_states[static_cast<int>(KeyMod::left_shift)] = (mod_state == KMOD_LSHIFT || mod_state == KMOD_SHIFT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::right_shift)] = (mod_state == KMOD_RSHIFT || mod_state == KMOD_SHIFT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::left_alt)] = (mod_state == KMOD_LALT || mod_state == KMOD_ALT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::right_alt)] = (mod_state == KMOD_RALT || mod_state == KMOD_ALT) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::left_control)] = (mod_state == KMOD_LCTRL || mod_state == KMOD_CTRL) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::right_control)] = (mod_state == KMOD_RCTRL || mod_state == KMOD_CTRL) ? KeyState::pressed : KeyState::released;
                keymod_states[static_cast<int>(KeyMod::caps_lock)] = (mod_state == KMOD_CAPS) ? KeyState::pressed : KeyState::released;

                KeyState state = _sdl_event.key.state == 1 ? KeyState::pressed : KeyState::released;
                Key key(sdl_keysym_to_keycode_conversion(_sdl_event.key.keysym), state, keymod_states);

                uint32_t window = _sdl_event.key.windowID;
                bool repeat = _sdl_event.key.repeat == 1;

                KeyboardMsgArgs* args = zero_new KeyboardMsgArgs(time, window, key, repeat);

                return _factory->create_message(AppMsg::keyboard, args);
                /*
                if (_sdl_event.type == SDL_KEYDOWN) {
                    return _factory->create_message(AppMsg::keydown, args);
                } else {
                    return _factory->create_message(AppMsg::keyup, args);
                }
                */
            }
            case SDL_TEXTEDITING:
                return _factory->create_message(AppMsg::text_edit, zero_new TextEditMsgArgs(time));
            case SDL_TEXTINPUT:
                return _factory->create_message(AppMsg::text_input, zero_new TextInputMsgArgs(time));
            case SDL_KEYMAPCHANGED:
                return _factory->create_message(AppMsg::keymap_changed, zero_new KeyMapChangedMsgArgs(time));
            case SDL_MOUSEMOTION:
            {

                uint32_t state = _sdl_event.motion.state;
                uint32_t mouse = _sdl_event.motion.which;
                uint32_t window = _sdl_event.motion.windowID;
                int32_t x_pos = _sdl_event.motion.x;
                int32_t y_pos = _sdl_event.motion.y;
                int32_t y_rel = _sdl_event.motion.yrel;
                int32_t x_rel = _sdl_event.motion.xrel;

                // SDL_MouseMotionEvent.state returns a bitmask of the current state of the mouse.
                // Perform bitwise & to check if a button is pressed.
                // This is equivilant of calling SDL_GetMouseState() & SDL_BUTTON(<button_number>)

                MouseButtonStateArray button_states;

                int left_button = static_cast<int>(MouseButton::left);
                button_states[left_button] = (state & 1 << (left_button - 1)) ? ButtonState::pressed : ButtonState::released;

                int middle_button = static_cast<int>(MouseButton::middle);
                button_states[middle_button] = (state & 1 << (middle_button - 1)) ? ButtonState::pressed : ButtonState::released;

                int right_button = static_cast<int>(MouseButton::right);
                button_states[right_button] = (state & 1 << (right_button - 1)) ? ButtonState::pressed : ButtonState::released;

                int button_four = static_cast<int>(MouseButton::four);
                button_states[button_four] = (state & 1 << (button_four - 1)) ? ButtonState::pressed : ButtonState::released;

                int button_five = static_cast<int>(MouseButton::five);
                button_states[button_five] = (state & 1 << (button_five - 1)) ? ButtonState::pressed : ButtonState::released;

                MouseMotionMsgArgs* args = 
                    zero_new MouseMotionMsgArgs(time, window, mouse, button_states, x_pos, y_pos, x_rel, y_rel);

                return _factory->create_message(AppMsg::mouse_motion, args);
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                uint32_t window = _sdl_event.button.windowID;
                uint32_t which = _sdl_event.button.which;
                ButtonState state = (_sdl_event.type == SDL_MOUSEBUTTONDOWN) ? ButtonState::pressed : ButtonState::released;
                uint8_t clicks = _sdl_event.button.clicks;

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

                int32_t x = _sdl_event.button.x;
                int32_t y = _sdl_event.button.y;

                MouseButtonMsgArgs* args = 
                    zero_new MouseButtonMsgArgs(time, window, which, state, clicks, button, x, y);

                if (_sdl_event.type == SDL_MOUSEBUTTONDOWN) {
                    return _factory->create_message(AppMsg::mouse_button_down, args);
                } else {
                    return _factory->create_message(AppMsg::mouse_button_up, args);
                }
            }

            // @TODO: Doesn't handle scrolling along x axis
            case SDL_MOUSEWHEEL:
            {
                uint32_t mouse = _sdl_event.wheel.which;
                uint32_t window = _sdl_event.wheel.windowID;
                int32_t x = _sdl_event.wheel.x;
                int32_t y = _sdl_event.wheel.y;

                // So the values are never flipped
                if (_sdl_event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
                    x *= -1;
                    y *= -1;
                }

                MouseWheelDirection direction = (y > 0) ? MouseWheelDirection::up : MouseWheelDirection::down;

                MouseWheelMsgArgs* args = zero_new MouseWheelMsgArgs(time, window, mouse, x, y, direction);

                return _factory->create_message(AppMsg::mouse_wheel, args);
            }

            case SDL_JOYAXISMOTION:
                return _factory->create_message(AppMsg::joy_axis_motion, zero_new JoyAxisMotionMsgArgs(time));
            case SDL_JOYBALLMOTION:
                return _factory->create_message(AppMsg::joy_ball_motion, zero_new JoyBallMotionMsgArgs(time));
            case SDL_JOYHATMOTION:
                return _factory->create_message(AppMsg::joy_hat_motion, zero_new JoyHatMotionMsgArgs(time));
            case SDL_JOYBUTTONDOWN:
                return _factory->create_message(AppMsg::joy_button_down, zero_new JoyButtonMsgArgs(time));
            case SDL_JOYBUTTONUP:
                return _factory->create_message(AppMsg::joy_button_up, zero_new JoyButtonMsgArgs(time));
            case SDL_JOYDEVICEADDED:
                return _factory->create_message(AppMsg::joy_device_added, zero_new JoyDeviceAddedMsgArgs(time));
            case SDL_JOYDEVICEREMOVED:
                return _factory->create_message(AppMsg::joy_device_removed, zero_new JoyDeviceRemovedMsgArgs(time));
            case SDL_CONTROLLERAXISMOTION:
                return _factory->create_message(AppMsg::controller_axis_motion, zero_new ControllerAxisMotionMsgArgs(time));
            case SDL_CONTROLLERBUTTONDOWN:
                return _factory->create_message(AppMsg::controller_button_down, zero_new ControllerButtonMsgArgs(time));
            case SDL_CONTROLLERBUTTONUP:
                return _factory->create_message(AppMsg::controller_button_up, zero_new ControllerButtonMsgArgs(time));
            case SDL_CONTROLLERDEVICEADDED:
                return _factory->create_message(AppMsg::controller_device_added, zero_new ControllerDeviceAddedMsgArgs(time));
            case SDL_CONTROLLERDEVICEREMOVED:
                return _factory->create_message(AppMsg::controller_device_removed, zero_new ControllerDeviceRemovedMsgArgs(time));
            case SDL_CONTROLLERDEVICEREMAPPED:
                return _factory->create_message(AppMsg::controller_device_remapped, zero_new ControllerDeviceRemappedMsgArgs(time));
            case SDL_FINGERUP:
                return _factory->create_message(AppMsg::finger_up, zero_new FingerUpMsgArgs(time));
            case SDL_FINGERDOWN:
                return _factory->create_message(AppMsg::finger_down, zero_new FingerDownMsgArgs(time));
            case SDL_FINGERMOTION:
                return _factory->create_message(AppMsg::finger_motion, zero_new FingerMotionMsgArgs(time));
            case SDL_DOLLARGESTURE:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_DOLLARRECORD:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_MULTIGESTURE:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            case SDL_CLIPBOARDUPDATE:
                return _factory->create_message(AppMsg::clipboard, zero_new ClipboardMsgArgs(time));
            case SDL_DROPFILE:
                return _factory->create_message(AppMsg::drop_file, zero_new DropFileMsgArgs(time));
            case SDL_DROPTEXT:
                return _factory->create_message(AppMsg::drop_text, zero_new DropTextMsgArgs(time));
            case SDL_DROPBEGIN:
                return _factory->create_message(AppMsg::drop_begin, zero_new DropBeginMsgArgs(time));
            case SDL_DROPCOMPLETE:
                return _factory->create_message(AppMsg::drop_complete, zero_new DropCompleteMsgArgs(time));
            case SDL_AUDIODEVICEADDED:
                return _factory->create_message(AppMsg::audio_device_added, zero_new AudioDeviceAddedMsgArgs(time));
            case SDL_AUDIODEVICEREMOVED:
                return _factory->create_message(AppMsg::audio_device_removed, zero_new AudioDeviceRemovedMsgArgs(time));
            case SDL_RENDER_TARGETS_RESET:
                return _factory->create_message(AppMsg::render_targets_reset, zero_new RenderTargetsResetMsgArgs(time));
            case SDL_RENDER_DEVICE_RESET:
                return _factory->create_message(AppMsg::render_device_reset, zero_new RenderDeviceResetMsgArgs(time));
            case SDL_USEREVENT:
                return _factory->create_message(AppMsg::unhandled, zero_new EmptyMsgArgs(time));
            default:
                // This should never be reached, but just in case
                return _factory->create_message(AppMsg::null, zero_new EmptyMsgArgs(time));
        }
    }

    void SdlMsgTranslator::set_sdl_event_to_translate(const SDL_Event& event) {
        _sdl_event = event;
    }

    KeyCode sdl_keysym_to_keycode_conversion(SDL_Keysym keysym) {
        switch (keysym.sym) {
            case SDLK_0:
                return KeyCode::zero;
            case SDLK_1:
                return KeyCode::one;
            case SDLK_2:
                return KeyCode::two;
            case SDLK_3:
                return KeyCode::three;
            case SDLK_4:
                return KeyCode::four;
            case SDLK_5:
                return KeyCode::five;
            case SDLK_6:
                return KeyCode::six;
            case SDLK_7:
                return KeyCode::seven;
            case SDLK_8:
                return KeyCode::eight;
            case SDLK_9:
                return KeyCode::nine;
            case SDLK_a:
                return KeyCode::a;
            case SDLK_b:
                return KeyCode::b;
            case SDLK_c:
                return KeyCode::c;
            case SDLK_d:
                return KeyCode::d;
            case SDLK_e:
                return KeyCode::e;
            case SDLK_f:
                return KeyCode::f;
            case SDLK_g:
                return KeyCode::g;
            case SDLK_h:
                return KeyCode::h;
            case SDLK_i:
                return KeyCode::i;
            case SDLK_j:
                return KeyCode::j;
            case SDLK_k:
                return KeyCode::k;
            case SDLK_l:
                return KeyCode::l;
            case SDLK_m:
                return KeyCode::m;
            case SDLK_n:
                return KeyCode::n;
            case SDLK_o:
                return KeyCode::o;
            case SDLK_p:
                return KeyCode::p;
            case SDLK_q:
                return KeyCode::q;
            case SDLK_r:
                return KeyCode::r;
            case SDLK_s:
                return KeyCode::s;
            case SDLK_t:
                return KeyCode::t;
            case SDLK_u:
                return KeyCode::u;
            case SDLK_v:
                return KeyCode::v;
            case SDLK_w:
                return KeyCode::w;
            case SDLK_x:
                return KeyCode::x;
            case SDLK_y:
                return KeyCode::y;
            case SDLK_z:
                return KeyCode::z;
            case SDLK_UP:
                return KeyCode::up;
            case SDLK_RIGHT:
                return KeyCode::right;
            case SDLK_DOWN:
                return KeyCode::down;
            case SDLK_LEFT:
                return KeyCode::left;
            case SDLK_ESCAPE:
                return KeyCode::escape;
            case SDLK_BACKSPACE:
                return KeyCode::backspace;
            case SDLK_RETURN:
                return KeyCode::enter;
            case SDLK_LCTRL:
                return KeyCode::left_control;
            case SDLK_RCTRL:
                return KeyCode::right_control;
            case SDLK_LALT:
                return KeyCode::left_alt;
            case SDLK_RALT:
                return KeyCode::right_alt;
            case SDLK_LSHIFT:
                return KeyCode::left_shift;
            case SDLK_RSHIFT:
                return KeyCode::right_shift;
            case SDLK_TAB:
                return KeyCode::tab;
            case SDLK_DELETE:
                return KeyCode::del;
            case SDLK_SPACE:
                return KeyCode::space;
            case SDLK_AMPERSAND:
                return KeyCode::ampersand;
            case SDLK_ASTERISK:
                return KeyCode::asterisk;
            case SDLK_AT:
                return KeyCode::at;
            case SDLK_CARET:
                return KeyCode::caret;
            case SDLK_COLON:
                return KeyCode::colon;
            case SDLK_DOLLAR:
                return KeyCode::dollar;
            case SDLK_EXCLAIM:
                return KeyCode::exclamation;
            case SDLK_GREATER:
                return KeyCode::greater_than;
            case SDLK_HASH:
                return KeyCode::hash;
            case SDLK_LEFTPAREN:
                return KeyCode::left_paren;
            case SDLK_RIGHTPAREN:
                return KeyCode::right_paren;
            case SDLK_LESS:
                return KeyCode::less_than;
            case SDLK_PERCENT:
                return KeyCode::percent;
            case SDLK_PLUS:
                return KeyCode::plus;
            case SDLK_QUESTION:
                return KeyCode::question_mark;
            case SDLK_QUOTEDBL:
                return KeyCode::double_quote;
            case SDLK_UNDERSCORE:
                return KeyCode::underscore;
            case SDLK_SLASH:
                return KeyCode::forward_slash;
            case SDLK_BACKSLASH:
                return KeyCode::back_slash;
            case SDLK_SEMICOLON:
                return KeyCode::semicolon;
            case SDLK_RIGHTBRACKET:
                return KeyCode::right_bracket;
            case SDLK_PERIOD:
                return KeyCode::period;
            case SDLK_MINUS:
                return KeyCode::minus;
            case SDLK_LEFTBRACKET:
                return KeyCode::left_bracket;
            case SDLK_EQUALS:
                return KeyCode::equal;
            case SDLK_COMMA:
                return KeyCode::comma;
            case SDLK_QUOTE:
                return KeyCode::single_quote;
            case SDLK_BACKQUOTE:
                return KeyCode::tilda;
            case SDLK_PAGEDOWN:
                return KeyCode::page_down;
            case SDLK_PAGEUP:
                return KeyCode::page_up;
            case SDLK_CAPSLOCK:
                return KeyCode::caps_lock;
            default:
                return KeyCode::null;
        }
    }
}

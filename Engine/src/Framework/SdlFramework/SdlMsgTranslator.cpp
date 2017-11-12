#include "SdlMsgTranslator.h"

namespace ZeroEngine {

    static Key sdl_keysym_to_key_value_conversion(SDL_Keysym);

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
                return _factory->create_message(AppMsg::window, zero_new WindowMsgArgs(time));
            case SDL_SYSWMEVENT:
                return _factory->create_message(AppMsg::system, zero_new SystemMsgArgs(time));
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                uint32_t window = _sdl_event.key.windowID;
                bool repeat = _sdl_event.key.repeat == 1;
                KeyState state = _sdl_event.key.state == 1 ? KeyState::pressed : KeyState::released;
                Key key(sdl_keysym_to_key_value_conversion(_sdl_event.key.keysym));

                KeyboardMsgArgs* args = zero_new KeyboardMsgArgs(time, window, key, repeat, state);

                if (_sdl_event.type == SDL_KEYDOWN) {
                    return _factory->create_message(AppMsg::keydown, args);
                } else {
                    return _factory->create_message(AppMsg::keyup, args);
                }
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

                ButtonState button_states[static_cast<int>(MouseButton::end)];

                button_states[static_cast<int>(MouseButton::left)] = 
                    (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) ? ButtonState::pressed : ButtonState::released;
                button_states[static_cast<int>(MouseButton::middle)] = 
                    (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) ? ButtonState::pressed : ButtonState::released;
                button_states[static_cast<int>(MouseButton::right)] = 
                    (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) ? ButtonState::pressed : ButtonState::released;
                button_states[static_cast<int>(MouseButton::four)] = 
                    (SDL_GetMouseState(nullptr, nullptr) & 1 << (static_cast<int>(MouseButton::four) - 1)) ? ButtonState::pressed : ButtonState::released;
                button_states[static_cast<int>(MouseButton::five)] = 
                    (SDL_GetMouseState(nullptr, nullptr) & 1 << (static_cast<int>(MouseButton::five) - 1)) ? ButtonState::pressed : ButtonState::released;

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

            case SDL_MOUSEWHEEL:
                return _factory->create_message(AppMsg::mouse_wheel, zero_new MouseWheelMsgArgs(time));
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

    Key sdl_keysym_to_key_value_conversion(SDL_Keysym keysym) {
        SDL_Keycode keycode = keysym.sym;
        bool shift_pressed = keysym.mod == KMOD_SHIFT || keysym.mod == KMOD_LSHIFT || keysym.mod == KMOD_RSHIFT;

        switch (keycode) {
            case SDLK_0:
                return shift_pressed ? KeyValue::right_paren : KeyValue::zero;
            case SDLK_1:
                return shift_pressed ? KeyValue::exclamation : KeyValue::one;
            case SDLK_2:
                return shift_pressed ? KeyValue::at : KeyValue::two;
            case SDLK_3:
                return shift_pressed ? KeyValue::hash : KeyValue::three;
            case SDLK_4:
                return shift_pressed ? KeyValue::dollar : KeyValue::four;
            case SDLK_5:
                return shift_pressed ? KeyValue::percent : KeyValue::five;
            case SDLK_6:
                return shift_pressed ? KeyValue::caret : KeyValue::six;
            case SDLK_7:
                return shift_pressed ? KeyValue::ampersand : KeyValue::seven;
            case SDLK_8:
                return shift_pressed ? KeyValue::asterisk : KeyValue::eight;
            case SDLK_9:
                return shift_pressed ? KeyValue::left_paren : KeyValue::nine;
            case SDLK_a:
                return shift_pressed ? KeyValue::A : KeyValue::a;
            default:
                return KeyValue::null;
        }
    }
}

#include "SdlMsgTranslator.h"

namespace ZeroEngine {

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
                return _factory->create_message(AppMsg::keydown, zero_new KeyboardMsgArgs(time));
            case SDL_KEYUP:
                return _factory->create_message(AppMsg::keyup, zero_new KeyboardMsgArgs(time));
            case SDL_TEXTEDITING:
                return _factory->create_message(AppMsg::text_edit, zero_new TextEditMsgArgs(time));
            case SDL_TEXTINPUT:
                return _factory->create_message(AppMsg::text_input, zero_new TextInputMsgArgs(time));
            case SDL_KEYMAPCHANGED:
                return _factory->create_message(AppMsg::keymap_changed, zero_new KeyMapChangedMsgArgs(time));
            case SDL_MOUSEMOTION:
                return _factory->create_message(AppMsg::mouse_motion, zero_new MouseMotionMsgArgs(time));
            case SDL_MOUSEBUTTONDOWN:
                return _factory->create_message(AppMsg::mouse_button_down, zero_new MouseButtonMsgArgs(time));
            case SDL_MOUSEBUTTONUP:
                return _factory->create_message(AppMsg::mouse_button_up, zero_new MouseButtonMsgArgs(time));
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
}

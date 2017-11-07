#include "SdlMessageTranslator.h"

namespace ZeroEngine {

    AppMsgType SdlMsgTranslator::translate_message(FrameworkMsgId id) {
        return _translation_map[id];
    }

    // TODO: _translation_map can be optimized.
    // The array is initialized to 65543 (0xffff) because
    // of the SDL_Event enum.
    void SdlMsgTranslator::init_translation_map() {
        for (int i = SDL_FIRSTEVENT; i < SDL_LASTEVENT; ++i) {
            _translation_map[i] = NULL_MSG;
        }
        _translation_map[SDL_QUIT] = QUIT_MSG;
        _translation_map[SDL_APP_TERMINATING] = UNHANDLED_MSG;
        _translation_map[SDL_APP_LOWMEMORY] = UNHANDLED_MSG;
        _translation_map[SDL_APP_WILLENTERBACKGROUND] = UNHANDLED_MSG;
        _translation_map[SDL_APP_DIDENTERBACKGROUND] = UNHANDLED_MSG;
        _translation_map[SDL_APP_WILLENTERFOREGROUND] = UNHANDLED_MSG;
        _translation_map[SDL_APP_DIDENTERFOREGROUND] = UNHANDLED_MSG;
        _translation_map[SDL_WINDOWEVENT] = WINDOW_MSG;
        _translation_map[SDL_SYSWMEVENT] = SYSTEM_MSG;
        _translation_map[SDL_KEYDOWN] = KEYDOWN_MSG;
        _translation_map[SDL_KEYUP] = KEYUP_MSG;
        _translation_map[SDL_TEXTEDITING] = TEXT_EDIT_MSG;
        _translation_map[SDL_TEXTINPUT] = TEXT_INPUT_MSG;
        _translation_map[SDL_KEYMAPCHANGED] = KEYMAP_CHANGE_MSG;
        _translation_map[SDL_MOUSEMOTION] = MOUSE_MOTION_MSG;
        _translation_map[SDL_MOUSEBUTTONDOWN] = MOUSE_BUTTON_DOWN_MSG;
        _translation_map[SDL_MOUSEBUTTONUP] = MOUSE_BUTTON_UP_MSG;
        _translation_map[SDL_MOUSEWHEEL] = MOUSE_WHEEL_MSG;
        _translation_map[SDL_JOYAXISMOTION] = JOY_AXIS_MOTION_MSG;
        _translation_map[SDL_JOYBALLMOTION] = JOY_BALL_MOTION_MSG;
        _translation_map[SDL_JOYHATMOTION] = JOY_HAT_MOTION_MSG;
        _translation_map[SDL_JOYBUTTONDOWN] = JOY_BUTTON_DOWN_MSG;
        _translation_map[SDL_JOYBUTTONUP] = JOY_BUTTON_UP_MSG;
        _translation_map[SDL_JOYDEVICEADDED] = JOY_DEVICE_ADDED_MSG;
        _translation_map[SDL_JOYDEVICEREMOVED] = JOY_DEVICE_REMOVED_MSG;
        _translation_map[SDL_CONTROLLERAXISMOTION] = CONTROLLER_AXIS_MOTION_MSG;
        _translation_map[SDL_CONTROLLERBUTTONDOWN] = CONTROLLER_BUTTON_DOWN_MSG;
        _translation_map[SDL_CONTROLLERBUTTONUP] = CONTROLLER_BUTTON_UP_MSG;
        _translation_map[SDL_CONTROLLERDEVICEADDED] = CONTROLLER_DEVICE_ADDED_MSG;
        _translation_map[SDL_CONTROLLERDEVICEREMOVED] = CONTROLLER_DEVICE_REMOVED_MSG;
        _translation_map[SDL_CONTROLLERDEVICEREMAPPED] = CONTROLLER_DEVICE_REMAPPED_MSG;
        _translation_map[SDL_FINGERDOWN] = FINGER_DOWN_MSG;
        _translation_map[SDL_FINGERUP] = FINGER_UP_MSG;
        _translation_map[SDL_FINGERMOTION] = FINGER_MOTION_MSG;
        _translation_map[SDL_DOLLARGESTURE] = UNHANDLED_MSG;
        _translation_map[SDL_DOLLARRECORD] = UNHANDLED_MSG;
        _translation_map[SDL_MULTIGESTURE] = UNHANDLED_MSG;
        _translation_map[SDL_CLIPBOARDUPDATE] = CLIPBOARD_MSG;
        _translation_map[SDL_DROPFILE] = DROP_FILE_MSG;
        _translation_map[SDL_DROPTEXT] = DROP_TEXT_MSG;
        _translation_map[SDL_DROPBEGIN] = DROP_BEGIN_MSG;
        _translation_map[SDL_DROPCOMPLETE] = DROP_COMPLETE_MSG;
        _translation_map[SDL_AUDIODEVICEADDED] = AUDIO_DEVICE_ADDED_MSG;
        _translation_map[SDL_AUDIODEVICEREMOVED] = AUDIO_DEVICE_REMOVED_MSG;
        _translation_map[SDL_RENDER_TARGETS_RESET] = RENDER_TARGETS_RESET_MSG;
        _translation_map[SDL_RENDER_DEVICE_RESET] = RENDER_DEVICE_RESET_MSG;
        _translation_map[SDL_USEREVENT] = UNHANDLED_MSG;
    }
}

/*
inline void init_zero_names() {
for (int i = MSG_BEGIN; i < MSG_END; ++i) {
_zero_msg_names[i] = std::string("NULL_MSG");
}
_zero_msg_names[QUIT_MSG]= std::string("QUIT_MSG");
_zero_msg_names[UNHANDLED_MSG] = std::string("UNHANDLED_MSG");
_zero_msg_names[WINDOW_MSG] = std::string("WINDOW_MSG");
_zero_msg_names[SYSTEM_MSG] = std::string("SYSTEM_MSG");
_zero_msg_names[KEYDOWN_MSG] = std::string("KEYDOWN_MSG");
_zero_msg_names[KEYUP_MSG] = std::string("KEYUP_MSG");
_zero_msg_names[TEXT_EDIT_MSG] = std::string("TEXT_EDIT_MSG");
_zero_msg_names[TEXT_INPUT_MSG] = std::string("TEXT_INPUT_MSG");
_zero_msg_names[KEYMAP_CHANGE_MSG] = std::string("KEYMAP_CHANGE_MSG");
_zero_msg_names[MOUSE_MOTION_MSG] = std::string("MOUSE_MOTION_MSG");
_zero_msg_names[MOUSE_BUTTON_DOWN_MSG] = std::string("MOUSE_BUTTON_DOWN_MSG");
_zero_msg_names[MOUSE_BUTTON_UP_MSG] = std::string("MOUSE_BUTTON_UP_MSG");
_zero_msg_names[MOUSE_WHEEL_MSG] = std::string("MOUSE_WHEEL_MSG");
_zero_msg_names[JOY_AXIS_MOTION_MSG] = std::string("JOY_AXIS_MOTION_MSG");
_zero_msg_names[JOY_BALL_MOTION_MSG] = std::string("JOY_BALL_MOTION_MSG");
_zero_msg_names[JOY_HAT_MOTION_MSG] = std::string("JOY_HAT_MOTION_MSG");
_zero_msg_names[JOY_BUTTON_DOWN_MSG] = std::string("JOY_BUTTON_DOWN_MSG");
_zero_msg_names[JOY_BUTTON_UP_MSG] = std::string("JOY_BUTTON_UP_MSG");
_zero_msg_names[JOY_DEVICE_ADDED_MSG] = std::string("JOY_DEVICE_ADDED_MSG");
_zero_msg_names[JOY_DEVICE_REMOVED_MSG] = std::string("JOY_DEVICE_REMOVED_MSG");
_zero_msg_names[CONTROLLER_AXIS_MOTION_MSG] = std::string("CONTROLLER_AXIS_MOTION_MSG");
_zero_msg_names[CONTROLLER_BUTTON_DOWN_MSG] = std::string("CONTROLLER_BUTTON_DOWN_MSG");
_zero_msg_names[CONTROLLER_BUTTON_UP_MSG] = std::string("CONTROLLER_BUTTON_UP_MSG");
_zero_msg_names[CONTROLLER_DEVICE_ADDED_MSG] = std::string("CONTROLLER_DEVICE_ADDED_MSG");
_zero_msg_names[CONTROLLER_DEVICE_REMOVED_MSG] = std::string("CONTROLLER_DEVICE_REMOVED_MSG");
_zero_msg_names[CONTROLLER_DEVICE_REMAPPED_MSG] = std::string("CONTROLLER_DEVICE_REMAPPED_MSG");
_zero_msg_names[FINGER_DOWN_MSG] = std::string("FINGER_DOWN_MSG");
_zero_msg_names[FINGER_UP_MSG] = std::string("FINGER_UP_MSG");
_zero_msg_names[FINGER_MOTION_MSG] = std::string("FINGER_MOTION_MSG");
_zero_msg_names[CLIPBOARD_MSG] = std::string("CLIPBOARD_MSG");
_zero_msg_names[DROP_FILE_MSG] = std::string("DROP_FILE_MSG");
_zero_msg_names[DROP_TEXT_MSG] = std::string("DROP_TEXT_MSG");
_zero_msg_names[DROP_BEGIN_MSG] = std::string("DROP_BEGIN_MSG");
_zero_msg_names[DROP_COMPLETE_MSG] = std::string("DROP_COMPLETE_MSG");
_zero_msg_names[AUDIO_DEVICE_ADDED_MSG] = std::string("AUDIO_DEVICE_ADDED_MSG");
_zero_msg_names[AUDIO_DEVICE_REMOVED_MSG] = std::string("AUDIO_DEVICE_REMOVED_MSG");
_zero_msg_names[RENDER_TARGETS_RESET_MSG] = std::string("RENDER_TARGETS_RESET_MSG");
_zero_msg_names[RENDER_DEVICE_RESET_MSG] = std::string("RENDER_DEVICE_RESET_MSG");
}
inline void init_sdl_names() {
for (int i = SDL_FIRSTEVENT; i < SDL_LASTEVENT; ++i) {
_sdl_event_names[i] = std::string("SDL_NULL");
}
_sdl_event_names[SDL_QUIT] = std::string("SDL_QUIT");
_sdl_event_names[SDL_APP_TERMINATING] = std::string("SDL_APP_TERMINATING");
_sdl_event_names[SDL_APP_LOWMEMORY] = std::string("SDL_APP_LOWMEMORY");
_sdl_event_names[SDL_APP_WILLENTERBACKGROUND] = std::string("SDL_APP_WILLENTERBACKGROUND");
_sdl_event_names[SDL_APP_DIDENTERBACKGROUND] = std::string("SDL_APP_DIDENTERBACKGROUND");
_sdl_event_names[SDL_APP_WILLENTERFOREGROUND] = std::string("SDL_APP_WILLENTERFOREGROUND");
_sdl_event_names[SDL_APP_DIDENTERFOREGROUND] = std::string("SDL_APP_DIDENTERFOREGROUND");
_sdl_event_names[SDL_WINDOWEVENT] = std::string("SDL_WINDOWEVENT");
_sdl_event_names[SDL_SYSWMEVENT] = std::string("SDL_SYSWMEVENT");
_sdl_event_names[SDL_KEYDOWN] = std::string("SDL_KEYDOWN");
_sdl_event_names[SDL_KEYUP] = std::string("SDL_KEYUP");
_sdl_event_names[SDL_TEXTEDITING] = std::string("SDL_TEXTEDITING");
_sdl_event_names[SDL_TEXTINPUT] = std::string("SDL_TEXTINPUT");
_sdl_event_names[SDL_KEYMAPCHANGED] = std::string("SDL_KEYMAPCHANGED");
_sdl_event_names[SDL_MOUSEMOTION] = std::string("SDL_MOUSEMOTION");
_sdl_event_names[SDL_MOUSEBUTTONDOWN] = std::string("SDL_MOUSEBUTTONDOWN");
_sdl_event_names[SDL_MOUSEBUTTONUP] = std::string("SDL_MOUSEBUTTONUP");
_sdl_event_names[SDL_MOUSEWHEEL] = std::string("SDL_MOUSEWHEEL");
_sdl_event_names[SDL_JOYAXISMOTION] = std::string("SDL_JOYAXISMOTION");
_sdl_event_names[SDL_JOYBALLMOTION] = std::string("SDL_JOYBALLMOTION");
_sdl_event_names[SDL_JOYHATMOTION] = std::string("SDL_JOYHATMOTION");
_sdl_event_names[SDL_JOYBUTTONDOWN] = std::string("SDL_JOYBUTTONDOWN");
_sdl_event_names[SDL_JOYBUTTONUP] = std::string("SDL_JOYBUTTONUP");
_sdl_event_names[SDL_JOYDEVICEADDED] = std::string("SDL_JOYDEVICEADDED");
_sdl_event_names[SDL_JOYDEVICEREMOVED] = std::string("SDL_JOYDEVICEREMOVED");
_sdl_event_names[SDL_CONTROLLERAXISMOTION] = std::string("SDL_CONTROLLERAXISMOTION");
_sdl_event_names[SDL_CONTROLLERBUTTONDOWN] = std::string("SDL_CONTROLLERBUTTONDOWN");
_sdl_event_names[SDL_CONTROLLERBUTTONUP] = std::string("SDL_CONTROLLERBUTTONUP");
_sdl_event_names[SDL_CONTROLLERDEVICEADDED] = std::string("SDL_CONTROLLERDEVICEADDED");
_sdl_event_names[SDL_CONTROLLERDEVICEREMOVED] = std::string("SDL_CONTROLLERDEVICEREMOVED");
_sdl_event_names[SDL_CONTROLLERDEVICEREMAPPED] = std::string("SDL_CONTROLLERDEVICEREMAPPED");
_sdl_event_names[SDL_FINGERDOWN] = std::string("SDL_FINGERDOWN");
_sdl_event_names[SDL_FINGERUP] = std::string("SDL_FINGERUP");
_sdl_event_names[SDL_FINGERMOTION] = std::string("SDL_FINGERMOTION");
_sdl_event_names[SDL_DOLLARGESTURE] = std::string("SDL_DOLLARGESTURE");
_sdl_event_names[SDL_DOLLARRECORD] = std::string("SDL_DOLLARRECORD");
_sdl_event_names[SDL_MULTIGESTURE] = std::string("SDL_MULTIGESTURE");
_sdl_event_names[SDL_CLIPBOARDUPDATE] = std::string("SDL_CLIPBOARDUPDATE");
_sdl_event_names[SDL_DROPFILE] = std::string("SDL_DROPFILE");
_sdl_event_names[SDL_DROPTEXT] = std::string("SDL_DROPTEXT");
_sdl_event_names[SDL_DROPBEGIN] = std::string("SDL_DROPBEGIN");
_sdl_event_names[SDL_DROPCOMPLETE] = std::string("SDL_DROPCOMPLETE");
_sdl_event_names[SDL_AUDIODEVICEADDED] = std::string("SDL_AUDIODEVICEADDED");
_sdl_event_names[SDL_AUDIODEVICEREMOVED] = std::string("SDL_AUDIODEVICEREMOVED");
_sdl_event_names[SDL_RENDER_TARGETS_RESET] = std::string("SDL_RENDER_TARGETS_RESET");
_sdl_event_names[SDL_RENDER_DEVICE_RESET] = std::string("SDL_RENDER_DEVICE_RESET");
_sdl_event_names[SDL_USEREVENT] = std::string("SDL_USEREVENT");
}
*/
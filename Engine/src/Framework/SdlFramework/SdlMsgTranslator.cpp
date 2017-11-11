#include "SdlMsgTranslator.h"

namespace ZeroEngine {

    // TODO: _translation_map can be optimized.
    // The array is initialized to 65535 (0xffff) because
    // of the SDL_Event enum.
    void SdlMsgTranslator::init_translation_map() {
        for (int i = SDL_FIRSTEVENT; i < SDL_LASTEVENT; ++i) {
            _translation_map[i] = AppMsg::null;
        }
        _translation_map[SDL_QUIT] = AppMsg::quit;
        _translation_map[SDL_APP_TERMINATING] = AppMsg::unhandled;
        _translation_map[SDL_APP_LOWMEMORY] = AppMsg::unhandled;
        _translation_map[SDL_APP_WILLENTERBACKGROUND] = AppMsg::unhandled;
        _translation_map[SDL_APP_DIDENTERBACKGROUND] = AppMsg::unhandled;
        _translation_map[SDL_APP_WILLENTERFOREGROUND] = AppMsg::unhandled;
        _translation_map[SDL_APP_DIDENTERFOREGROUND] = AppMsg::unhandled; 
        _translation_map[SDL_WINDOWEVENT] = AppMsg::window;
        _translation_map[SDL_SYSWMEVENT] = AppMsg::system;
        _translation_map[SDL_KEYDOWN] = AppMsg::keydown;
        _translation_map[SDL_KEYUP] = AppMsg::keyup;
        _translation_map[SDL_TEXTEDITING] = AppMsg::text_edit;
        _translation_map[SDL_TEXTINPUT] = AppMsg::text_input;
        _translation_map[SDL_KEYMAPCHANGED] = AppMsg::keymap_changed;
        _translation_map[SDL_MOUSEMOTION] = AppMsg::mouse_motion;
        _translation_map[SDL_MOUSEBUTTONDOWN] = AppMsg::mouse_button_down;
        _translation_map[SDL_MOUSEBUTTONUP] = AppMsg::mouse_button_up;
        _translation_map[SDL_MOUSEWHEEL] = AppMsg::mouse_wheel;
        _translation_map[SDL_JOYAXISMOTION] = AppMsg::joy_axis_motion;
        _translation_map[SDL_JOYBALLMOTION] = AppMsg::joy_ball_motion;
        _translation_map[SDL_JOYHATMOTION] = AppMsg::joy_hat_motion;
        _translation_map[SDL_JOYBUTTONDOWN] = AppMsg::joy_button_down;
        _translation_map[SDL_JOYBUTTONUP] = AppMsg::joy_button_up;
        _translation_map[SDL_JOYDEVICEADDED] = AppMsg::joy_device_added;
        _translation_map[SDL_JOYDEVICEREMOVED] = AppMsg::joy_device_removed;
        _translation_map[SDL_CONTROLLERAXISMOTION] = AppMsg::controller_axis_motion;
        _translation_map[SDL_CONTROLLERBUTTONDOWN] = AppMsg::controller_button_down;
        _translation_map[SDL_CONTROLLERBUTTONUP] = AppMsg::controller_button_up;
        _translation_map[SDL_CONTROLLERDEVICEADDED] = AppMsg::controller_device_added;
        _translation_map[SDL_CONTROLLERDEVICEREMOVED] = AppMsg::controller_device_removed;
        _translation_map[SDL_CONTROLLERDEVICEREMAPPED] = AppMsg::controller_device_remapped;
        _translation_map[SDL_FINGERDOWN] = AppMsg::finger_down;
        _translation_map[SDL_FINGERUP] = AppMsg::finger_up;
        _translation_map[SDL_FINGERMOTION] = AppMsg::finger_motion;
        _translation_map[SDL_DOLLARGESTURE] = AppMsg::unhandled;
        _translation_map[SDL_DOLLARRECORD] = AppMsg::unhandled;
        _translation_map[SDL_MULTIGESTURE] = AppMsg::unhandled;
        _translation_map[SDL_CLIPBOARDUPDATE] = AppMsg::clipboard;
        _translation_map[SDL_DROPFILE] = AppMsg::drop_file;
        _translation_map[SDL_DROPTEXT] = AppMsg::drop_text;
        _translation_map[SDL_DROPBEGIN] = AppMsg::drop_begin;
        _translation_map[SDL_DROPCOMPLETE] = AppMsg::drop_complete;
        _translation_map[SDL_AUDIODEVICEADDED] = AppMsg::audio_device_added;
        _translation_map[SDL_AUDIODEVICEREMOVED] = AppMsg::audio_device_removed;
        _translation_map[SDL_RENDER_TARGETS_RESET] = AppMsg::render_targets_reset;
        _translation_map[SDL_RENDER_DEVICE_RESET] = AppMsg::render_device_reset;
        _translation_map[SDL_USEREVENT] = AppMsg::unhandled;
    }

    AppMsg& SdlMsgTranslator::get_translated_message() {
        return _factory->create_message(_translation_map[_sdl_event_to_translate.type]);
    }


    void SdlMsgTranslator::set_sdl_event_to_translate(const SDL_Event& event) {
        _sdl_event_to_translate = event;
    }
}

/*
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
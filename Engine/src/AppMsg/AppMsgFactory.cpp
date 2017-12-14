#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        _access_key = AppMsgAccessKey();
        AppMsg::init_memory_pool(_access_key);
        _creation_map = zero_new std::map<AppMsgType, app_msg_creation_delegate>();
        register_app_messages();
        _current_message = get_app_message(AppMsgType::null, zero_new EmptyMsgArgs(0));
    }

    AppMsgFactory::~AppMsgFactory() {
        AppMsg::destroy(_access_key, _current_message);
        _current_message = nullptr;
        zero_delete(_creation_map);
        AppMsg::destroy_memory_pool(_access_key);
    }

    const AppMsg* const AppMsgFactory::create_message(AppMsgType msg_type, AppMsgArgs* args) {
        AppMsg::destroy(_access_key, _current_message);
        _current_message = get_app_message(msg_type, args);
        return _current_message;
    }

    AppMsg* AppMsgFactory::get_app_message(AppMsgType msg_type, AppMsgArgs* args) {
        assert(_creation_map != nullptr);

        std::map<AppMsgType, app_msg_creation_delegate>::iterator iter;

        iter = _creation_map->find(msg_type);

        if (iter == _creation_map->end()) {
            std::cout << "ERROR. AppMsgFactory create_message() failed.\n";
            // create NullMsg on error
            assert( msg_type != AppMsgType::null);
            iter = _creation_map->find(AppMsgType::null);
        }

        app_msg_creation_delegate delegate = iter->second;

        return delegate(_access_key, args);
    }

    void AppMsgFactory::register_app_messages() {
        assert(_creation_map != nullptr);
        _creation_map->insert(std::make_pair(AppMsgType::null, NullMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::quit, QuitMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::unhandled, UnhandledMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::window, WindowMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::system, SystemMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::keydown, KeydownMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::keyup, KeyupMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::text_edit, TextEditMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::text_input, TextInputMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::keymap_changed, KeymapChangedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::mouse_motion, MouseMotionMsg::create)); 
        _creation_map->insert(std::make_pair(AppMsgType::mouse_button_down, MouseButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::mouse_button_up, MouseButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::mouse_wheel, MouseWheelMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_axis_motion, JoyAxisMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_ball_motion, JoyBallMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_hat_motion, JoyHatMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_button_down, JoyButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_button_up, JoyButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_device_added, JoyDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::joy_device_removed, JoyDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_axis_motion, ControllerAxisMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_button_down, ControllerButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_button_up, ControllerButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_device_added, ControllerDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_device_removed, ControllerDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::controller_device_remapped, ControllerDeviceRemappedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::finger_down, FingerDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::finger_up, FingerUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::finger_motion, FingerMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::clipboard, ClipboardMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::drop_file, DropFileMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::drop_text, DropTextMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::drop_begin, DropBeginMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::drop_complete, DropCompleteMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::audio_device_added, AudioDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::audio_device_removed, AudioDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::render_targets_reset, RenderTargetsResetMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::render_device_reset, RenderDeviceResetMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::keyboard, KeyboardMsg::create));
        _creation_map->insert(std::make_pair(AppMsgType::mouse_button, MouseButtonMsg::create));
    }
}
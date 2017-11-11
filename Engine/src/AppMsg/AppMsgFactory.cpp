#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        _access_key = AppMsgAccessKey();
        AppMsg::init_memory_pool(_access_key);
        _creation_map = zero_new std::map<AppMsgType, app_msg_creation_delegate>();
        register_app_messages();
        _current_message = get_app_message(AppMsg::null);
    }

    AppMsgFactory::~AppMsgFactory() {
        AppMsg::destroy(_access_key, _current_message);
        _current_message = nullptr;
        zero_delete(_creation_map);
        AppMsg::destroy_memory_pool(_access_key);
    }

    AppMsg* AppMsgFactory::create_message(AppMsgType msg_type) {
        AppMsg::destroy(_access_key, _current_message);
        _current_message = get_app_message(msg_type);
        return _current_message;
    }

    // @@TODO: this function wont work since the args arn't being passed in through the ctor
    // All derived classes should override set_args()
    AppMsg* AppMsgFactory::create_message(AppMsgType msg_type, AppMsgArgs* args) {
        create_message(msg_type);
        _current_message->set_args(_access_key, args);
        return _current_message;
    }

    AppMsg* AppMsgFactory::get_app_message(AppMsgType msg_type) {
        assert(_creation_map != nullptr);
        std::map<AppMsgType, app_msg_creation_delegate>::iterator iter;
        iter = _creation_map->find(msg_type);
        if (iter == _creation_map->end()) {
            std::cout << "ERROR. AppMsgFactory create_message() failed.\n";
            // create NullMsg on error
            assert( msg_type != AppMsg::null);
            iter = _creation_map->find(AppMsg::null);
        }
        app_msg_creation_delegate delegate = iter->second;
        // TOOD:
        // MsgArgs takes in time. Make Time class so I can call Time::zero or something
        return delegate(_access_key, zero_new EmptyMsgArgs(0));
    }

    void AppMsgFactory::register_app_messages() {
        assert(_creation_map != nullptr);
        _creation_map->insert(std::make_pair(AppMsg::null, NullMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::quit, QuitMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::unhandled, UnhandledMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::window, WindowMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::system, SystemMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::keydown, KeyDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::keyup, KeyUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::text_edit, TextEditMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::text_input, TextInputMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::keymap_changed, KeyMapChangedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::mouse_motion, MouseMotionMsg::create)); 
        _creation_map->insert(std::make_pair(AppMsg::mouse_button_down, MouseButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::mouse_button_up, MouseButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::mouse_wheel, MouseWheelMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_axis_motion, JoyAxisMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_ball_motion, JoyBallMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_hat_motion, JoyHatMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_button_down, JoyButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_button_up, JoyButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_device_added, JoyDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::joy_device_removed, JoyDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_axis_motion, ControllerAxisMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_button_down, ControllerButtonDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_button_up, ControllerButtonUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_device_added, ControllerDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_device_removed, ControllerDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::controller_device_remapped, ControllerDeviceRemappedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::finger_down, FingerDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::finger_up, FingerUpMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::finger_motion, FingerMotionMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::clipboard, ClipboardMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::drop_file, DropFileMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::drop_text, DropTextMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::drop_begin, DropBeginMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::drop_complete, DropCompleteMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::audio_device_added, AudioDeviceAddedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::audio_device_removed, AudioDeviceRemovedMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::render_targets_reset, RenderTargetsResetMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::render_device_reset, RenderDeviceResetMsg::create));
    }
}
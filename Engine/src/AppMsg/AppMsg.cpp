#include "AppMsg.h"

namespace ZeroEngine {

    MemoryPool* AppMsg::_memory_pool = nullptr;
    #ifdef _DEBUG
    int AppMsg::_allocations = 0;
    #endif

    AppMsg::AppMsg(AppMsgArgs* args) {
        _args = args;
        #ifdef _DEBUG
        print_creation_data();
        #endif
    }

    AppMsg::~AppMsg() {
        zero_delete(_args);
        #ifdef _DEBUG
        print_deletion_data();
        #endif
    }

    void AppMsg::init_memory_pool(AppMsgAccessKey& key) {
        if (_memory_pool == nullptr) {
            _memory_pool = zero_new MemoryPool();
            // !! @@TODO: Need to find largest derived and base size off of that
            // sizeof(AppMsg) causes heap corruption
            _memory_pool->initialize(64, 1);
        }
    }

    void AppMsg::destroy_memory_pool(AppMsgAccessKey& key) {
        if (_memory_pool != nullptr) {
            zero_delete(_memory_pool);
        }
    }

    void* AppMsg::operator new(size_t size) {
        assert(_memory_pool != nullptr);
        void* memory = _memory_pool->allocate();
        return memory;
    }

    void AppMsg::operator delete(void* ptr) {
        assert(_memory_pool != nullptr);
        _memory_pool->free_memory(ptr);
    }

    void AppMsg::operator delete[](void* ptr) {
        assert(_memory_pool != nullptr);
        _memory_pool->free_memory(ptr);
    }

    void* AppMsg::operator new[](size_t size) {
        assert(_memory_pool != nullptr);
        void* memory = _memory_pool->allocate();
        return memory;
    }

    #ifdef _DEBUG
    void AppMsg::print_creation_data() {
        ++_allocations;
        // std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        --_allocations;
        // std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif

    //
    // NullMsg
    //

    const AppMsgType NullMsg::type = AppMsgType::null;

    AppMsg* NullMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new NullMsg(args);
    }

    NullMsg::ptr NullMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<NullMsg::ptr>(msg);
    }

    //
    // QuitMsg
    //

    const AppMsgType QuitMsg::type = AppMsgType::quit;

    AppMsg* QuitMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new QuitMsg(args);
    }

    QuitMsg::ptr QuitMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<QuitMsg::ptr>(msg);
    }


    //
    // UnhandledMsg
    //

    const AppMsgType UnhandledMsg::type = AppMsgType::unhandled;

    AppMsg* UnhandledMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new UnhandledMsg(args);
    }

    UnhandledMsg::ptr UnhandledMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<UnhandledMsg::ptr>(msg);
    }

    // 
    // WindowMsg
    //

    const AppMsgType WindowMsg::type = AppMsgType::window;

    AppMsg* WindowMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new WindowMsg(args);
    }

    WindowMsg::ptr WindowMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<WindowMsg::ptr>(msg);
    }

    WindowMsg::WindowMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<WindowMsgArgs*>(args);
    }

    //
    // SystemMsg
    //

    const AppMsgType SystemMsg::type = AppMsgType::system;

    AppMsg* SystemMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new SystemMsg(args);
    }

    SystemMsg::ptr SystemMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<SystemMsg::ptr>(msg);
    }

    SystemMsg::SystemMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<SystemMsgArgs*>(args);
    }

    //
    // KeyboardMsg
    //

    const AppMsgType KeyboardMsg::type = AppMsgType::keyboard;

    AppMsg* KeyboardMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyboardMsg(args);
    }

    KeyboardMsg::ptr KeyboardMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<KeyboardMsg::ptr>(msg);
    }

    KeyboardMsg::KeyboardMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }

    //
    // KeyDownMsg
    //

    const AppMsgType KeydownMsg::type = AppMsgType::keydown;

    AppMsg* KeydownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeydownMsg(args);
    }

    KeydownMsg::ptr KeydownMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<KeydownMsg::ptr>(msg);
    }

    KeydownMsg::KeydownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }


    //
    // KeyUpMsg
    //

    const AppMsgType KeyupMsg::type = AppMsgType::keyup;

    AppMsg* KeyupMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyupMsg(args);
    }

    KeyupMsg::ptr KeyupMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<KeyupMsg::ptr>(msg);
    }

    KeyupMsg::KeyupMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }


    //
    // TextEditMsg
    //

    const AppMsgType TextEditMsg::type = AppMsgType::text_edit;

    AppMsg* TextEditMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new TextEditMsg(args);
    }

    TextEditMsg::ptr TextEditMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<TextEditMsg::ptr>(msg);
    }

    TextEditMsg::TextEditMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextEditMsgArgs*>(args);
    }

    //
    // TextInputMsg
    //

    const AppMsgType TextInputMsg::type = AppMsgType::text_input;

    AppMsg* TextInputMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new TextInputMsg(args);
    }

    TextInputMsg::ptr TextInputMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<TextInputMsg::ptr>(msg);
    }

    TextInputMsg::TextInputMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextInputMsgArgs*>(args);
    }

    //
    // KeyMapChangedMsg
    //

    const AppMsgType KeymapChangedMsg::type = AppMsgType::keymap_changed;

    AppMsg* KeymapChangedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeymapChangedMsg(args);
    }

    KeymapChangedMsg::ptr KeymapChangedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<KeymapChangedMsg::ptr>(msg);
    }

    KeymapChangedMsg::KeymapChangedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyMapChangedMsgArgs*>(args);
    }

    // 
    // MouseButtonDownMsg
    //

    const AppMsgType MouseButtonDownMsg::type = AppMsgType::mouse_button_down;

    AppMsg* MouseButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonDownMsg(args);
    }

    MouseButtonDownMsg::ptr MouseButtonDownMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<MouseButtonDownMsg::ptr>(msg);
    }

    MouseButtonDownMsg::MouseButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    //
    // MouseButtonUpMsg
    //

    const AppMsgType MouseButtonUpMsg::type = AppMsgType::mouse_button_up;

    AppMsg* MouseButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonUpMsg(args);
    }

    MouseButtonUpMsg::ptr MouseButtonUpMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<MouseButtonUpMsg::ptr>(msg);
    }

    MouseButtonUpMsg::MouseButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    //
    // MouseButtonMsg
    //

    const AppMsgType MouseButtonMsg::type = AppMsgType::mouse_button;

    AppMsg* MouseButtonMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonMsg(args);
    }

    MouseButtonMsg::ptr MouseButtonMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<MouseButtonMsg::ptr>(msg);
    }

    MouseButtonMsg::MouseButtonMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    //
    // MouseWheelMsg
    //

    const AppMsgType MouseWheelMsg::type = AppMsgType::mouse_wheel;

    AppMsg* MouseWheelMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseWheelMsg(args);
    }

    MouseWheelMsg::ptr MouseWheelMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<MouseWheelMsg::ptr>(msg);
    }

    MouseWheelMsg::MouseWheelMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseWheelMsgArgs*>(args);
    }

    //
    // MouseMotionMsg
    //

    const AppMsgType MouseMotionMsg::type = AppMsgType::mouse_motion;

    AppMsg* MouseMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseMotionMsg(args);
    }

    MouseMotionMsg::ptr MouseMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<MouseMotionMsg::ptr>(msg);
    }

    MouseMotionMsg::MouseMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseMotionMsgArgs*>(args);
    }

    //
    // JoyAxisMotionMsg
    //

    const AppMsgType JoyAxisMotionMsg::type = AppMsgType::joy_axis_motion;

    AppMsg* JoyAxisMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyAxisMotionMsg(args);
    }

    JoyAxisMotionMsg::ptr JoyAxisMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyAxisMotionMsg::ptr>(msg);
    }

    JoyAxisMotionMsg::JoyAxisMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyAxisMotionMsgArgs*>(args);
    }

    //
    // JoyBallMotionMsg
    //

    const AppMsgType JoyBallMotionMsg::type = AppMsgType::joy_ball_motion;

    AppMsg* JoyBallMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyBallMotionMsg(args);
    }

    JoyBallMotionMsg::ptr JoyBallMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyBallMotionMsg::ptr>(msg);
    }

    JoyBallMotionMsg::JoyBallMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyBallMotionMsgArgs*>(args);
    }

    //
    // JoyHatMotionMsg
    //

    const AppMsgType JoyHatMotionMsg::type = AppMsgType::joy_hat_motion;

    AppMsg* JoyHatMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyHatMotionMsg(args);
    }

    JoyHatMotionMsg::ptr JoyHatMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyHatMotionMsg::ptr>(msg);
    }

    JoyHatMotionMsg::JoyHatMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyHatMotionMsgArgs*>(args);
    }

    //
    // JoyButtonDownMsg
    //

    const AppMsgType JoyButtonDownMsg::type = AppMsgType::joy_button_down;

    AppMsg* JoyButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyButtonDownMsg(args);
    }

    JoyButtonDownMsg::ptr JoyButtonDownMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyButtonDownMsg::ptr>(msg);
    }

    JoyButtonDownMsg::JoyButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyButtonMsgArgs*>(args);
    }

    //
    // JoyButtonUpMsg
    //

    const AppMsgType JoyButtonUpMsg::type = AppMsgType::joy_button_up;

    AppMsg* JoyButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyButtonUpMsg(args);
    }

    JoyButtonUpMsg::ptr JoyButtonUpMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyButtonUpMsg::ptr>(msg);
    }

    JoyButtonUpMsg::JoyButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyButtonMsgArgs*>(args);
    }

    //
    // JoyDeviceAddedMsg
    //

    const AppMsgType JoyDeviceAddedMsg::type = AppMsgType::joy_device_added;

    AppMsg* JoyDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyDeviceAddedMsg(args);
    }

    JoyDeviceAddedMsg::ptr JoyDeviceAddedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyDeviceAddedMsg::ptr>(msg);
    }

    JoyDeviceAddedMsg::JoyDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyDeviceAddedMsgArgs*>(args);
    }

    //
    // JoyDeviceRemovedMsg
    //

    const AppMsgType JoyDeviceRemovedMsg::type = AppMsgType::joy_device_removed;

    AppMsg* JoyDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyDeviceRemovedMsg(args);
    }

    JoyDeviceRemovedMsg::ptr JoyDeviceRemovedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<JoyDeviceRemovedMsg::ptr>(msg);
    }

    JoyDeviceRemovedMsg::JoyDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyDeviceRemovedMsgArgs*>(args);
    }

    //
    // ControllerAxisMotionMsg
    //

    const AppMsgType ControllerAxisMotionMsg::type = AppMsgType::controller_axis_motion;

    AppMsg* ControllerAxisMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerAxisMotionMsg(args);
    }

    ControllerAxisMotionMsg::ptr ControllerAxisMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerAxisMotionMsg::ptr>(msg);
    }

    ControllerAxisMotionMsg::ControllerAxisMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerAxisMotionMsgArgs*>(args);
    }

    //
    // ControllerButtonDownMsg
    //

    const AppMsgType ControllerButtonDownMsg::type = AppMsgType::controller_button_down;

    AppMsg* ControllerButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerButtonDownMsg(args);
    }

    ControllerButtonDownMsg::ptr ControllerButtonDownMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerButtonDownMsg::ptr>(msg);
    }

    ControllerButtonDownMsg::ControllerButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerButtonMsgArgs*>(args);
    }

    //
    // ControllerButtonUpMsg
    //

    const AppMsgType ControllerButtonUpMsg::type = AppMsgType::controller_button_up;

    AppMsg* ControllerButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerButtonUpMsg(args);
    }

    ControllerButtonUpMsg::ptr ControllerButtonUpMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerButtonUpMsg::ptr>(msg);
    }

    ControllerButtonUpMsg::ControllerButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerButtonMsgArgs*>(args);
    }

    //
    // ControllerDeviceAddedMsg
    //

    const AppMsgType ControllerDeviceAddedMsg::type = AppMsgType::controller_device_added;

    AppMsg* ControllerDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceAddedMsg(args);
    }

    ControllerDeviceAddedMsg::ptr ControllerDeviceAddedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerDeviceAddedMsg::ptr>(msg);
    }

    ControllerDeviceAddedMsg::ControllerDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceAddedMsgArgs*>(args);
    }

    //
    // ControllerDeviceRemovedMsg
    //

    const AppMsgType ControllerDeviceRemovedMsg::type = AppMsgType::controller_device_removed;

    AppMsg* ControllerDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceRemovedMsg(args);
    }

    ControllerDeviceRemovedMsg::ptr ControllerDeviceRemovedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerDeviceRemovedMsg::ptr>(msg);
    }

    ControllerDeviceRemovedMsg::ControllerDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceRemovedMsgArgs*>(args);
    }

    //
    // ControllerDeviceRemappedMsg
    //

    const AppMsgType ControllerDeviceRemappedMsg::type = AppMsgType::controller_device_remapped;

    AppMsg* ControllerDeviceRemappedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceRemappedMsg(args);
    }

    ControllerDeviceRemappedMsg::ptr ControllerDeviceRemappedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ControllerDeviceRemappedMsg::ptr>(msg);
    }

    ControllerDeviceRemappedMsg::ControllerDeviceRemappedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceRemappedMsgArgs*>(args);
    }

    //
    // FingerDownMsg
    //

    const AppMsgType FingerDownMsg::type = AppMsgType::finger_down;

    AppMsg* FingerDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerDownMsg(args);
    }

    FingerDownMsg::ptr FingerDownMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<FingerDownMsg::ptr>(msg);
    }

    FingerDownMsg::FingerDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerDownMsgArgs*>(args);
    }

    //
    // FingerUpMsg
    //

    const AppMsgType FingerUpMsg::type = AppMsgType::finger_up;

    AppMsg* FingerUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerUpMsg(args);
    }

    FingerUpMsg::ptr FingerUpMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<FingerUpMsg::ptr>(msg);
    }

    FingerUpMsg::FingerUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerUpMsgArgs*>(args);
    }

    //
    // FingerMotionMsg
    //

    const AppMsgType FingerMotionMsg::type = AppMsgType::finger_motion;

    AppMsg* FingerMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerMotionMsg(args);
    }

    FingerMotionMsg::ptr FingerMotionMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<FingerMotionMsg::ptr>(msg);
    }

    FingerMotionMsg::FingerMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerMotionMsgArgs*>(args);
    }

    //
    // ClipboardMsg
    //

    const AppMsgType ClipboardMsg::type = AppMsgType::clipboard;

    AppMsg* ClipboardMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ClipboardMsg(args);
    }

    ClipboardMsg::ptr ClipboardMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<ClipboardMsg::ptr>(msg);
    }

    ClipboardMsg::ClipboardMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ClipboardMsgArgs*>(args);
    }

    //
    // DropFileMsg
    //
        
    const AppMsgType DropFileMsg::type = AppMsgType::drop_file;

    AppMsg* DropFileMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropFileMsg(args);
    }

    DropFileMsg::ptr DropFileMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<DropFileMsg::ptr>(msg);
    }

    DropFileMsg::DropFileMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropFileMsgArgs*>(args);
    }

    //
    // DropTextMsg
    //

    const AppMsgType DropTextMsg::type = AppMsgType::drop_text;

    AppMsg* DropTextMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropTextMsg(args);
    }

    DropTextMsg::ptr DropTextMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<DropTextMsg::ptr>(msg);
    }

    DropTextMsg::DropTextMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropTextMsgArgs*>(args);
    }

    // 
    // DropBeginMsg
    //

    const AppMsgType DropBeginMsg::type = AppMsgType::drop_begin;

    AppMsg* DropBeginMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropBeginMsg(args);
    }

    DropBeginMsg::ptr DropBeginMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<DropBeginMsg::ptr>(msg);
    }

    DropBeginMsg::DropBeginMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropBeginMsgArgs*>(args);
    }

    //
    // DropCompleteMsg
    //

    const AppMsgType DropCompleteMsg::type = AppMsgType::drop_complete;

    AppMsg* DropCompleteMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropCompleteMsg(args);
    }

    DropCompleteMsg::ptr DropCompleteMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<DropCompleteMsg::ptr>(msg);
    }

    DropCompleteMsg::DropCompleteMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropCompleteMsgArgs*>(args);
    }

    //
    // AudioDeviceAddedMsg
    //

    const AppMsgType AudioDeviceAddedMsg::type = AppMsgType::audio_device_added;

    AppMsg* AudioDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new AudioDeviceAddedMsg(args);
    }

    AudioDeviceAddedMsg::ptr AudioDeviceAddedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<AudioDeviceAddedMsg::ptr>(msg);
    }

    AudioDeviceAddedMsg::AudioDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<AudioDeviceAddedMsgArgs*>(args);
    }

    //
    // AudioDeviceRemovedMsg
    //

    const AppMsgType AudioDeviceRemovedMsg::type = AppMsgType::audio_device_removed;

    AppMsg* AudioDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new AudioDeviceRemovedMsg(args);
    }

    AudioDeviceRemovedMsg::ptr AudioDeviceRemovedMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<AudioDeviceRemovedMsg::ptr>(msg);
    }

    AudioDeviceRemovedMsg::AudioDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<AudioDeviceRemovedMsgArgs*>(args);
    }

    //
    // RenderTargetsResetMsg
    //

    const AppMsgType RenderTargetsResetMsg::type = AppMsgType::render_targets_reset;

    AppMsg* RenderTargetsResetMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new RenderTargetsResetMsg(args);
    }

    RenderTargetsResetMsg::ptr RenderTargetsResetMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<RenderTargetsResetMsg::ptr>(msg);
    }

    RenderTargetsResetMsg::RenderTargetsResetMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<RenderTargetsResetMsgArgs*>(args);
    }

    //
    // RenderDeviceResetMsg
    //

    const AppMsgType RenderDeviceResetMsg::type = AppMsgType::render_device_reset;

    AppMsg* RenderDeviceResetMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new RenderDeviceResetMsg(args);
    }

    RenderDeviceResetMsg::ptr RenderDeviceResetMsg::cast(AppMsg::ptr msg) {
        assert(msg->is_type(type));
        return dynamic_cast<RenderDeviceResetMsg::ptr>(msg);
    }

    RenderDeviceResetMsg::RenderDeviceResetMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<RenderDeviceResetMsgArgs*>(args);
    }
}
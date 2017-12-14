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

    AppMsg* NullMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new NullMsg(args);
    }

    //
    // QuitMsg
    //

    AppMsg* QuitMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new QuitMsg(args);
    }


    //
    // UnhandledMsg
    //

    AppMsg* UnhandledMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new UnhandledMsg(args);
    }

    // 
    // WindowMsg
    //

    AppMsg* WindowMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new WindowMsg(args);
    }

    WindowMsg::WindowMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<WindowMsgArgs*>(args);
    }


    //
    // SystemMsg
    //

    AppMsg* SystemMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new SystemMsg(args);
    }

    SystemMsg::SystemMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<SystemMsgArgs*>(args);
    }

    //
    // KeyboardMsg
    //

    AppMsg* KeyboardMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyboardMsg(args);
    }

    KeyboardMsg::KeyboardMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }

    const KeyboardMsg* const KeyboardMsg::cast(const AppMsg* const msg) {
        assert(msg->get_type() == AppMsgType::keyboard);
        const KeyboardMsg* const ret = dynamic_cast<const KeyboardMsg* const>(msg);
        return ret;
    }

    //
    // KeyDownMsg
    //

    AppMsg* KeyDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyDownMsg(args);
    }

    KeyDownMsg::KeyDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }


    //
    // KeyUpMsg
    //

    AppMsg* KeyUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyUpMsg(args);
    }

    KeyUpMsg::KeyUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyboardMsgArgs*>(args);
    }


    //
    // TextEditMsg
    //

    AppMsg* TextEditMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new TextEditMsg(args);
    }

    TextEditMsg::TextEditMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextEditMsgArgs*>(args);
    }

    //
    // TextInputMsg
    //

    AppMsg* TextInputMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new TextInputMsg(args);
    }

    TextInputMsg::TextInputMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextInputMsgArgs*>(args);
    }

    //
    // KeyMapChangedMsg
    //

    AppMsg* KeyMapChangedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new KeyMapChangedMsg(args);
    }

    KeyMapChangedMsg::KeyMapChangedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyMapChangedMsgArgs*>(args);
    }

    // 
    // MouseButtonDownMsg
    //

    AppMsg* MouseButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonDownMsg(args);
    }

    MouseButtonDownMsg::MouseButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    //
    // MouseButtonUpMsg
    //

    AppMsg* MouseButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonUpMsg(args);
    }

    MouseButtonUpMsg::MouseButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    //
    // MouseButtonMsg
    //

    AppMsg* MouseButtonMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseButtonMsg(args);
    }

    MouseButtonMsg::MouseButtonMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseButtonMsgArgs*>(args);
    }

    const MouseButtonMsg* const MouseButtonMsg::cast(const AppMsg* const msg) {
        assert(msg->get_type() == AppMsgType::mouse_button);
        const MouseButtonMsg* const ret = dynamic_cast<const MouseButtonMsg* const>(msg);
        return ret;
    }

    //
    // MouseWheelMsg
    //

    AppMsg* MouseWheelMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseWheelMsg(args);
    }

    const MouseWheelMsg* const MouseWheelMsg::cast(const AppMsg* const msg) {
        assert(msg->get_type() == AppMsgType::mouse_wheel);
        const MouseWheelMsg* const ret = dynamic_cast<const MouseWheelMsg* const>(msg);
        return ret;
    }

    MouseWheelMsg::MouseWheelMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseWheelMsgArgs*>(args);
    }

    //
    // MouseMotionMsg
    //

    AppMsg* MouseMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new MouseMotionMsg(args);
    }

    MouseMotionMsg::MouseMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseMotionMsgArgs*>(args);
    }

    const MouseMotionMsg* const MouseMotionMsg::cast(const AppMsg* const msg) {
        assert(msg->get_type() == AppMsgType::mouse_motion);
        const MouseMotionMsg* const ret = dynamic_cast<const MouseMotionMsg* const>(msg);
        return ret;
    }

    //
    // JoyAxisMotionMsg
    //

    AppMsg* JoyAxisMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyAxisMotionMsg(args);
    }

    JoyAxisMotionMsg::JoyAxisMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyAxisMotionMsgArgs*>(args);
    }

    //
    // JoyBallMotionMsg
    //

    AppMsg* JoyBallMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyBallMotionMsg(args);
    }

    JoyBallMotionMsg::JoyBallMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyBallMotionMsgArgs*>(args);
    }

    //
    // JoyHatMotionMsg
    //

    AppMsg* JoyHatMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyHatMotionMsg(args);
    }

    JoyHatMotionMsg::JoyHatMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyHatMotionMsgArgs*>(args);
    }

    //
    // JoyButtonDownMsg
    //

    AppMsg* JoyButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyButtonDownMsg(args);
    }

    JoyButtonDownMsg::JoyButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyButtonMsgArgs*>(args);
    }

    //
    // JoyButtonUpMsg
    //

    AppMsg* JoyButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyButtonUpMsg(args);
    }

    JoyButtonUpMsg::JoyButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyButtonMsgArgs*>(args);
    }

    //
    // JoyDeviceAddedMsg
    //

    AppMsg* JoyDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyDeviceAddedMsg(args);
    }

    JoyDeviceAddedMsg::JoyDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyDeviceAddedMsgArgs*>(args);
    }

    //
    // JoyDeviceRemovedMsg
    //

    AppMsg* JoyDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new JoyDeviceRemovedMsg(args);
    }

    JoyDeviceRemovedMsg::JoyDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<JoyDeviceRemovedMsgArgs*>(args);
    }

    //
    // ControllerAxisMotionMsg
    //

    AppMsg* ControllerAxisMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerAxisMotionMsg(args);
    }

    ControllerAxisMotionMsg::ControllerAxisMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerAxisMotionMsgArgs*>(args);
    }

    //
    // ControllerAxisButtonDownMsg
    //

    AppMsg* ControllerButtonDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerButtonDownMsg(args);
    }

    ControllerButtonDownMsg::ControllerButtonDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerButtonMsgArgs*>(args);
    }

    //
    // ControllerAxisButtonUpMsg
    //

    AppMsg* ControllerButtonUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerButtonUpMsg(args);
    }

    ControllerButtonUpMsg::ControllerButtonUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerButtonMsgArgs*>(args);
    }

    //
    // ControllerDeviceAddedMsg
    //

    AppMsg* ControllerDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceAddedMsg(args);
    }

    ControllerDeviceAddedMsg::ControllerDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceAddedMsgArgs*>(args);
    }

    //
    // ControllerDeviceRemovedMsg
    //

    AppMsg* ControllerDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceRemovedMsg(args);
    }

    ControllerDeviceRemovedMsg::ControllerDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceRemovedMsgArgs*>(args);
    }

    //
    // ControllerDeviceRemappedMsg
    //

    AppMsg* ControllerDeviceRemappedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ControllerDeviceRemappedMsg(args);
    }

    ControllerDeviceRemappedMsg::ControllerDeviceRemappedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ControllerDeviceRemappedMsgArgs*>(args);
    }

    //
    // FingerDownMsg
    //

    AppMsg* FingerDownMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerDownMsg(args);
    }

    FingerDownMsg::FingerDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerDownMsgArgs*>(args);
    }

    //
    // FingerUpMsg
    //

    AppMsg* FingerUpMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerUpMsg(args);
    }

    FingerUpMsg::FingerUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerUpMsgArgs*>(args);
    }

    //
    // FingerMotionMsg
    //

    AppMsg* FingerMotionMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new FingerMotionMsg(args);
    }

    FingerMotionMsg::FingerMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<FingerMotionMsgArgs*>(args);
    }

    //
    // ClipboardMsg
    //

    AppMsg* ClipboardMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new ClipboardMsg(args);
    }

    ClipboardMsg::ClipboardMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<ClipboardMsgArgs*>(args);
    }

    //
    // DropFileMsg
    //
        
    AppMsg* DropFileMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropFileMsg(args);
    }

    DropFileMsg::DropFileMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropFileMsgArgs*>(args);
    }

    //
    // DropTextMsg
    //

    AppMsg* DropTextMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropTextMsg(args);
    }

    DropTextMsg::DropTextMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropTextMsgArgs*>(args);
    }

    // 
    // DropBeginMsg
    //

    AppMsg* DropBeginMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropBeginMsg(args);
    }

    DropBeginMsg::DropBeginMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropBeginMsgArgs*>(args);
    }

    //
    // DropCompleteMsg
    //

    AppMsg* DropCompleteMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new DropCompleteMsg(args);
    }

    DropCompleteMsg::DropCompleteMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<DropCompleteMsgArgs*>(args);
    }

    //
    // AudioDeviceAddedMsg
    //

    AppMsg* AudioDeviceAddedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new AudioDeviceAddedMsg(args);
    }

    AudioDeviceAddedMsg::AudioDeviceAddedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<AudioDeviceAddedMsgArgs*>(args);
    }

    //
    // AudioDeviceRemovedMsg
    //

    AppMsg* AudioDeviceRemovedMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new AudioDeviceRemovedMsg(args);
    }

    AudioDeviceRemovedMsg::AudioDeviceRemovedMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<AudioDeviceRemovedMsgArgs*>(args);
    }

    //
    // RenderTargetsResetMsg
    //

    AppMsg* RenderTargetsResetMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new RenderTargetsResetMsg(args);
    }

    RenderTargetsResetMsg::RenderTargetsResetMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<RenderTargetsResetMsgArgs*>(args);
    }

    //
    // RenderDeviceResetMsg
    //

    AppMsg* RenderDeviceResetMsg::create(AppMsgAccessKey& key, AppMsgArgs* args) {
        return new RenderDeviceResetMsg(args);
    }

    RenderDeviceResetMsg::RenderDeviceResetMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<RenderDeviceResetMsgArgs*>(args);
    }
}
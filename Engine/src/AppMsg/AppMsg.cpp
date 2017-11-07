#include "AppMsg.h"

namespace ZeroEngine {

    MemoryPool* AppMsg::_memory_pool = nullptr;
    #ifdef _DEBUG
    int AppMsg::_allocations = 0;
    #endif

    const AppMsgType AppMsg::null = 0x01;
    const AppMsgType AppMsg::quit = 0x02;
    const AppMsgType AppMsg::unhandled = 0x03;
    const AppMsgType AppMsg::window = 0x04;
    const AppMsgType AppMsg::system = 0x05;
    const AppMsgType AppMsg::keydown = 0x06;
    const AppMsgType AppMsg::keyup = 0x07;
    const AppMsgType AppMsg::text_edit = 0x08;
    const AppMsgType AppMsg::text_input = 0x09;
    const AppMsgType AppMsg::keymap_changed = 0x0A;
    const AppMsgType AppMsg::mouse_motion = 0x0B;
    const AppMsgType AppMsg::mouse_button_down = 0x0C;
    const AppMsgType AppMsg::mouse_button_up = 0x0D;
    const AppMsgType AppMsg::mouse_wheel = 0x0E;
    const AppMsgType AppMsg::joy_axis_motion = 0x0F;
    const AppMsgType AppMsg::joy_ball_motion = 0x10;
    const AppMsgType AppMsg::joy_hat_motion = 0x11;
    const AppMsgType AppMsg::joy_button_down = 0x12;
    const AppMsgType AppMsg::joy_button_up = 0x13;
    const AppMsgType AppMsg::joy_device_added = 0x14;
    const AppMsgType AppMsg::joy_device_removed = 0x15;
    const AppMsgType AppMsg::controller_axis_motion = 0x16;
    const AppMsgType AppMsg::controller_button_down = 0x17;
    const AppMsgType AppMsg::controller_button_up = 0x18;
    const AppMsgType AppMsg::controller_device_added = 0x19;
    const AppMsgType AppMsg::controller_device_removed = 0x1A;
    const AppMsgType AppMsg::controller_device_remapped = 0x1B;
    const AppMsgType AppMsg::finger_down = 0x1C;
    const AppMsgType AppMsg::finger_up = 0x1D;
    const AppMsgType AppMsg::finger_motion = 0x1E;
    const AppMsgType AppMsg::clipboard = 0x1F;
    const AppMsgType AppMsg::drop_file = 0x20;
    const AppMsgType AppMsg::drop_text = 0x21;
    const AppMsgType AppMsg::drop_begin = 0x22;
    const AppMsgType AppMsg::drop_complete = 0x23;
    const AppMsgType AppMsg::audio_device_added = 0x24;
    const AppMsgType AppMsg::audio_device_removed = 0x25;
    const AppMsgType AppMsg::render_targets_reset = 0x26;
    const AppMsgType AppMsg::render_device_reset = 0x27;

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

    void AppMsg::init_memory_pool() {
        if (_memory_pool == nullptr) {
            _memory_pool = zero_new MemoryPool();
            // !! @@TODO: Need to find largest derived and base size off of that
            // sizeof(AppMsg) causes heap corruption
            _memory_pool->initialize(64, 1);
        }
    }

    void AppMsg::destroy_memory_pool() {
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
        std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif



    //
    // NullMsg
    //

    AppMsg* NullMsg::create(AppMsgArgs* args) {
        return new NullMsg(args);
    }

    //
    // MouseMotionMsg
    //

    AppMsg* MouseMotionMsg::create(AppMsgArgs* args) {
        return new MouseMotionMsg(args);
    }

    MouseMotionMsg::MouseMotionMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<MouseMotionMsgArgs*>(args);
    }

    //
    // QuitMsg
    //

    AppMsg* QuitMsg::create(AppMsgArgs* args) {
        return new QuitMsg(args);
    }


    //
    // UnhandledMsg
    //

    AppMsg* UnhandledMsg::create(AppMsgArgs* args) {
        return new UnhandledMsg(args);
    }

    // 
    // WindowMsg
    //

    AppMsg* WindowMsg::create(AppMsgArgs* args) {
        return new WindowMsg(args);
    }

    WindowMsg::WindowMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<WindowMsgArgs*>(args);
    }


    //
    // SystemMsg
    //

    AppMsg* SystemMsg::create(AppMsgArgs* args) {
        return new SystemMsg(args);
    }

    SystemMsg::SystemMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<SystemMsgArgs*>(args);
    }

    //
    // KeyDownMsg
    //

    AppMsg* KeyDownMsg::create(AppMsgArgs* args) {
        return new KeyDownMsg(args);
    }

    KeyDownMsg::KeyDownMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyDownMsgArgs*>(args);
    }


    //
    // KeyUpMsg
    //

    AppMsg* KeyUpMsg::create(AppMsgArgs* args) {
        return new KeyUpMsg(args);
    }

    KeyUpMsg::KeyUpMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<KeyUpMsgArgs*>(args);
    }


    //
    // TextEditMsg
    //

    AppMsg* TextEditMsg::create(AppMsgArgs* args) {
        return new TextEditMsg(args);
    }

    TextEditMsg::TextEditMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextEditMsgArgs*>(args);
    }

    //
    // TextInputMsg
    //

    AppMsg* TextInputMsg::create(AppMsgArgs* args) {
        return new TextInputMsg(args);
    }

    TextInputMsg::TextInputMsg(AppMsgArgs* args) : AppMsg(args) {
        _args = dynamic_cast<TextInputMsgArgs*>(args);
    }





}
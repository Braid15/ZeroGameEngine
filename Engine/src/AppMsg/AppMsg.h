#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Utils/MemoryPool.h"
#include "AppMsgArgs.h"


//
// AppMsgFactory is a friend class to all AppMsg types to give it access to the protected static create() method.
// AppMsgFactory is not a friend class to base AppMsg class, which means that it cannot call the new or delete
// operators explicitly, but must do so through the static methods.



// @@TODO: AppMsg needs to take on the responsibliy of deleting instances
// insteade of AppMsgFactory and AppMsg needs to make it so only AppMsgFactory can
// create instances.
// @@TODO: Copyctors for AppMs

// @@TODO: Need some kind of referencing system since I won't be using share_ptr
// @@TODO: Who destroys MsgArgs*? AppMsg class or AppMsgArgs* creator? 


namespace ZeroEngine {

    typedef uint8_t AppMsgType;

    //
    // AppMsgAccessKey
    //
    //
    // Only friend classes of AppMsgAccessKey can instantiate it and an instance of AppMsgAccessKey is need
    // to access certain methods in AppMsg types.
    //

    class AppMsgAccessKey final : public IZeroObject {
    private:
        friend class AppMsgFactory;
        inline AppMsgAccessKey() {}
        inline ~AppMsgAccessKey() {}
        inline AppMsgAccessKey(const AppMsgAccessKey&) {}
    public:
        inline StringRepr to_string() const override { return "AppMsgAccessKey"; }
    };

    //
    // AppMsg
    //

    class AppMsg : public IZeroObject {
    private:
        static MemoryPool* _memory_pool;
        AppMsgArgs* _args;
        #ifdef _DEBUG
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
        #endif
    public:
        virtual const AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        inline Ticks get_time_stamp() const { return _args->get_creation_time(); }
        virtual inline void set_args(AppMsgAccessKey&, AppMsgArgs* args) { _args = args; }
        static void destroy(AppMsgAccessKey& key, AppMsg* msg) { delete msg; }
        static void init_memory_pool(AppMsgAccessKey&);
        static void destroy_memory_pool(AppMsgAccessKey&);

        static const AppMsgType null;
        static const AppMsgType quit;
        static const AppMsgType unhandled;
        static const AppMsgType window;
        static const AppMsgType system;
        static const AppMsgType keydown;
        static const AppMsgType keyup;
        static const AppMsgType keyboard;
        static const AppMsgType text_edit;
        static const AppMsgType text_input;
        static const AppMsgType keymap_changed;
        static const AppMsgType mouse_motion;
        static const AppMsgType mouse_button_down;
        static const AppMsgType mouse_button_up;
        static const AppMsgType mouse_button;
        static const AppMsgType mouse_wheel;
        static const AppMsgType joy_axis_motion;
        static const AppMsgType joy_ball_motion;
        static const AppMsgType joy_hat_motion;
        static const AppMsgType joy_button_down;
        static const AppMsgType joy_button_up;
        static const AppMsgType joy_device_added;
        static const AppMsgType joy_device_removed;
        static const AppMsgType controller_axis_motion;
        static const AppMsgType controller_button_down;
        static const AppMsgType controller_button_up;
        static const AppMsgType controller_device_added;
        static const AppMsgType controller_device_removed;
        static const AppMsgType controller_device_remapped;
        static const AppMsgType finger_down;
        static const AppMsgType finger_up;
        static const AppMsgType finger_motion;
        static const AppMsgType clipboard;
        static const AppMsgType drop_file;
        static const AppMsgType drop_text;
        static const AppMsgType drop_begin;
        static const AppMsgType drop_complete;
        static const AppMsgType audio_device_added;
        static const AppMsgType audio_device_removed;
        static const AppMsgType render_targets_reset;
        static const AppMsgType render_device_reset;

    protected:
        AppMsg(AppMsgArgs*);
        virtual ~AppMsg();
        inline AppMsgArgs& get_args() { return *_args; }
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
    };

    //
    // NullMsg
    //

    class NullMsg final : public AppMsg {
    public:
        inline StringRepr to_string() const override { return "NullMsg"; }
        inline const AppMsgType get_type() const override { return AppMsg::null; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~NullMsg() {}
    private:
        inline NullMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // QuitMsg
    //

    class QuitMsg final : public AppMsg {
    public:
        inline const AppMsgType get_type() const override { return AppMsg::quit; }
        inline StringRepr to_string() const override { return "QuitMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~QuitMsg() {}
    private:
        inline QuitMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // UnhandledMsg
    //

    class UnhandledMsg final : public AppMsg {
    public:
        inline const AppMsgType get_type() const override { return AppMsg::unhandled; }
        inline StringRepr to_string() const override { return "UnhandledMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~UnhandledMsg() {}
    private:
        inline UnhandledMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // WindowMsg
    //

    class WindowMsg final : public AppMsg {
    private:
        WindowMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::window; }
        inline StringRepr to_string() const override { return "WindowMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~WindowMsg() {}
    private:
        WindowMsg(AppMsgArgs*);
    };

    //
    // SystemMsg
    //

    class SystemMsg final : public AppMsg {
    private:
        SystemMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::system; }
        inline StringRepr to_string() const override { return "SystemMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~SystemMsg() {}
    private:
        SystemMsg(AppMsgArgs*);
    };

    //
    // KeyboardMsg
    //

    class KeyboardMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        // @TODO: Each class should have a cast method
        static const KeyboardMsg* const cast(const AppMsg* const);
        inline const AppMsgType get_type() const override { return AppMsg::keyboard; }
        inline StringRepr to_string() const override { return "KeyboardMsg"; }
        inline bool is_key(const Keys& keys) const { return key().equals(keys); }
        inline bool is_repeat() const { return _args->is_repeat(); }
        inline Key key() const { return _args->get_key(); }
        inline char get_key_char() const { return _args->get_key().get_key_char(); }
        inline uint32_t get_window() const { return _args->get_window(); }
        inline bool is_key_down() const { return _args->get_key().is_pressed(); }
        inline bool is_key_down(const Keys& key) const { return (is_key_down() && is_key(key)); }
        inline bool is_key_up() const { return !(_args->get_key().is_pressed()); }
        inline bool is_key_up(const Keys& key) const { return (is_key_up() && is_key(key)); }
        inline bool is_key_press() const { return (is_key_down() && !is_repeat()); }
        inline bool is_key_press(const Keys& key) const { return (is_key_down(key) && !is_repeat()); }
    protected:
        inline ~KeyboardMsg() {}
    private:
        KeyboardMsg(AppMsgArgs*);
    };
    
    //
    // KeyDownMsg
    //

    class KeyDownMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keydown; }
        inline StringRepr to_string() const override { return "KeyDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        inline bool is_repeat() const { return _args->is_repeat(); }
        inline Key get_key() const { return _args->get_key(); }
        inline char get_key_char() const { return _args->get_key().get_key_char(); }
        inline uint32_t get_window() const { return _args->get_window(); }
    protected:
        inline ~KeyDownMsg() {}
    private:
        KeyDownMsg(AppMsgArgs*);
    };

    //
    // KeyUpMsg
    //

    class KeyUpMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keyup; }
        inline StringRepr to_string() const override { return "KeyUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        inline bool is_repeat() const { return _args->is_repeat(); }
        inline Key get_key() const { return _args->get_key(); }
        inline char get_key_char() const { return _args->get_key().get_key_char(); }
        inline uint32_t get_window() const { return _args->get_window(); }
    protected:
        inline ~KeyUpMsg() {}
    private:
        KeyUpMsg(AppMsgArgs*);
    };

    //
    // TextEditMsg
    //

    class TextEditMsg final : public AppMsg {
    private:
        TextEditMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::text_edit; }
        inline StringRepr to_string() const override { return "TextEditMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~TextEditMsg() {}
    private:
        TextEditMsg(AppMsgArgs*);
    };

    //
    // TextInputMsg
    //

    class TextInputMsg final : public AppMsg {
    private:
        TextInputMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::text_input; }
        inline StringRepr to_string() const override { return "TextInputMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~TextInputMsg() {}
    private:
        TextInputMsg(AppMsgArgs*);
    };

    // 
    // KeyMapChangedMsg
    // 

    class KeyMapChangedMsg final : public AppMsg {
    private:
        KeyMapChangedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keymap_changed; }
        inline StringRepr to_string() const override { return "KeyMapChangedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~KeyMapChangedMsg() {}
    private:
        KeyMapChangedMsg(AppMsgArgs*);
    };

    // @TODO: MouseButtonMsg instead of MouseButtonUp/DOwn
    
    //
    // MouseButtonMsg
    //
    class MouseButtonMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static const MouseButtonMsg* const cast(const AppMsg* const);

        inline const AppMsgType get_type() const override { return AppMsg::mouse_button; }
        inline StringRepr to_string() const override { return "MouseButtonMsg"; }
        inline uint8_t get_num_clicks() const { return _args->get_num_clicks(); }
        inline int32_t get_x_pos() const { return _args->get_x_pos(); }
        inline int32_t get_y_pos() const { return _args->get_y_pos(); }
        inline Point<int32_t> get_coordinates() const { return _args->get_coordinates(); }
        inline MouseButton get_button() const { return _args->get_button(); }
        inline ButtonState get_state() const { return _args->get_state(); }
        inline bool is_button_up() const { return _args->get_state() == ButtonState::released; }
        inline bool is_button_down() const { return _args->get_state() == ButtonState::pressed; }
    protected:
        inline ~MouseButtonMsg() {}
    private:
        MouseButtonMsg(AppMsgArgs*);

    };
    //
    // MouseButtonDownMsg
    //

    class MouseButtonDownMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::mouse_button_down; }
        inline StringRepr to_string() const override { return "MouseButtonDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        inline uint8_t get_num_clicks() const { return _args->get_num_clicks(); }
        inline int32_t get_x_pos() const { return _args->get_x_pos(); }
        inline int32_t get_y_pos() const { return _args->get_y_pos(); }
        inline Point<int32_t> get_coordinates() const { return _args->get_coordinates(); }
        inline MouseButton get_button() const { return _args->get_button(); }
        inline ButtonState get_state() const { return _args->get_state(); }
    protected:
        inline ~MouseButtonDownMsg() {}
    private:
        MouseButtonDownMsg(AppMsgArgs*);
    };

    // 
    // MouseButtonUpMsg
    //

    class MouseButtonUpMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::mouse_button_up; }
        inline StringRepr to_string() const override { return "MouseButtonUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        inline uint8_t get_num_clicks() const { return _args->get_num_clicks(); }
        inline int32_t get_x_pos() const { return _args->get_x_pos(); }
        inline int32_t get_y_pos() const { return _args->get_y_pos(); }
        inline Point<int32_t> get_coordinates() const { return _args->get_coordinates(); }
        inline MouseButton get_button() const { return _args->get_button(); }
        inline ButtonState get_state() const { return _args->get_state(); }
    protected:
        inline ~MouseButtonUpMsg() {}
    private:
        MouseButtonUpMsg(AppMsgArgs*);
    };

    //
    // MouseMotionMsg
    //
   
    class MouseMotionMsg final : public AppMsg {
    private:
        MouseMotionMsgArgs* _args;
    public:
        static const MouseMotionMsg* const cast(const AppMsg* const);
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        inline const AppMsgType get_type() const override { return AppMsg::mouse_motion; }
        inline StringRepr to_string() const override { return "MouseMotionMsg"; }
        inline uint32_t get_window() const { return _args->get_window(); }
        inline uint32_t get_mouse_id() const { return _args->get_mouse_id(); }
        inline int32_t get_x_pos() const { return _args->get_x_pos(); }
        inline int32_t get_y_pos() const { return _args->get_y_pos(); }
        inline Point<int32_t> get_coordinates() const { return _args->get_coordinates(); }
        inline int32_t get_x_rel() const { return _args->get_x_rel(); }
        inline int32_t get_y_rel() const { return _args->get_y_rel(); }
        inline Point<int32_t> get_rel_coordinates() const { return _args->get_rel_coordinates(); }
        inline bool is_pressed(MouseButton button) const { return _args->is_pressed(button); }
        inline MouseButtonStateArray get_button_states() const { return _args->get_button_states(); }
    protected:
        inline ~MouseMotionMsg() {}
    private:
        MouseMotionMsg(AppMsgArgs*);
    };

    //
    // MouseWheelMsg
    //

    class MouseWheelMsg final : public AppMsg {
    private:
        MouseWheelMsgArgs* _args;
    public:
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static const MouseWheelMsg* const cast(const AppMsg* const);
        inline const AppMsgType get_type() const { return AppMsg::mouse_wheel; }
        inline StringRepr to_string() const { return "MouseWheenMsg"; }
        inline uint32_t get_window() const { return _args->get_window(); }
        inline uint32_t get_mouse() const { return _args->get_mouse(); }
        inline int32_t get_scroll_amount_x() const { return _args->get_scroll_amount_x(); }
        inline int32_t get_scroll_amount_y() const { return _args->get_scroll_amount_y(); }
        inline MouseWheelDirection get_direction() const { return _args->get_direction(); }
    protected:
        inline ~MouseWheelMsg() {}
    private:
        MouseWheelMsg(AppMsgArgs*);
    };

    // 
    // JoyAxisMotionMsg
    //

    class JoyAxisMotionMsg final : public AppMsg {
    private:
        JoyAxisMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_axis_motion; }
        inline StringRepr to_string() const override { return "JoyAxisMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyAxisMotionMsg() {}
    private:
        JoyAxisMotionMsg(AppMsgArgs*);
    };

    //
    // JoyBallMotionMsg
    //

    class JoyBallMotionMsg final : public AppMsg {
    private:
        JoyBallMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_ball_motion; }
        inline StringRepr to_string() const override { return "JoyBallMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyBallMotionMsg() {}
    private:
        JoyBallMotionMsg(AppMsgArgs*);
    };

    //
    // JoyHatMotionMsg
    //

    class JoyHatMotionMsg final : public AppMsg {
    private:
        JoyHatMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_hat_motion; }
        inline StringRepr to_string() const override { return "JoyHatMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyHatMotionMsg() {}
    private:
        JoyHatMotionMsg(AppMsgArgs*);
    };

    //
    // JoyButtonDownMsg
    //

    class JoyButtonDownMsg final : public AppMsg {
    private:
        JoyButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_button_down; }
        inline StringRepr to_string() const override { return "JoyButtonDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyButtonDownMsg() {}
    private:
        JoyButtonDownMsg(AppMsgArgs*);
    };

    //
    // JoyButtonUpMsg
    //

    class JoyButtonUpMsg final : public AppMsg {
    private:
        JoyButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_button_up; }
        inline StringRepr to_string() const override { return "JoyButtonUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyButtonUpMsg() {}
    private:
        JoyButtonUpMsg(AppMsgArgs*);
    };

    //
    // JoyDeviceAddedMsg
    //

    class JoyDeviceAddedMsg final : public AppMsg {
    private:
        JoyDeviceAddedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_device_added; }
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyDeviceAddedMsg() {}
    private:
        JoyDeviceAddedMsg(AppMsgArgs*);
    };

    //
    // JoyDeviceRemovedMsg
    //

    class JoyDeviceRemovedMsg final : public AppMsg {
    private:
        JoyDeviceRemovedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_device_removed; }
        inline StringRepr to_string() const override { return "JoyDeviceRemovedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyDeviceRemovedMsg() {}
    private:
        JoyDeviceRemovedMsg(AppMsgArgs*);
    };

    //
    // ControllerAxisMotionMsg
    //

    class ControllerAxisMotionMsg final : public AppMsg {
    private:
        ControllerAxisMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_axis_motion; }
        inline StringRepr to_string() const override { return "ControllerAxisMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerAxisMotionMsg() {}
    private:
        ControllerAxisMotionMsg(AppMsgArgs*);
    };

    //
    // ControllerAxisButtonDownMsg
    //

    // @TODO: Checkou if ControllerAxis or ControllerButton
    class ControllerButtonDownMsg final : public AppMsg {
    private:
        ControllerButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_button_up; }
        inline StringRepr to_string() const override { return "ControllerAxisButtonMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerButtonDownMsg() {}
    private:
        ControllerButtonDownMsg(AppMsgArgs*);
    };

    //
    // ControllerAxisButtonUpMsg
    //

    class ControllerButtonUpMsg final : public AppMsg {
    private:
        ControllerButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_button_up; }
        inline StringRepr to_string() const override { return "ControllerAxisButtonUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerButtonUpMsg() {}
    private:
        ControllerButtonUpMsg(AppMsgArgs*);
    };

    //
    // ControllerDeviceAddedMsg
    //

    class ControllerDeviceAddedMsg final : public AppMsg {
    private:
        ControllerDeviceAddedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_device_added; }
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerDeviceAddedMsg() {}
    private:
        ControllerDeviceAddedMsg(AppMsgArgs*);
    };

    //
    // ControllerDeviceRemovedMsg
    //

    class ControllerDeviceRemovedMsg final : public AppMsg {
    private:
        ControllerDeviceRemovedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_device_removed; }
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerDeviceRemovedMsg() {}
    private:
        ControllerDeviceRemovedMsg(AppMsgArgs*);
    };

    //
    // ControllerDeviceRemappedMsg
    //

    class ControllerDeviceRemappedMsg final : public AppMsg {
    private:
        ControllerDeviceRemappedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::controller_device_removed; }
        inline StringRepr to_string() const override { return "ControllerDeviceRemappedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ControllerDeviceRemappedMsg() {}
    private:
        ControllerDeviceRemappedMsg(AppMsgArgs*);
    };

    //
    // FingerDownMsg
    //

    class FingerDownMsg final : public AppMsg {
    private:
        FingerDownMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::finger_down; }
        inline StringRepr to_string() const override { return "FingerDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~FingerDownMsg() {}
    private:
        FingerDownMsg(AppMsgArgs*);
    };

    //
    // FingerUpMsg
    //

    class FingerUpMsg final : public AppMsg {
    private:
        FingerUpMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::finger_up; }
        inline StringRepr to_string() const override { return "FingerUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~FingerUpMsg() {}
    private:
        FingerUpMsg(AppMsgArgs*);
    };

    //
    // FingerMotionMsg
    //

    class FingerMotionMsg final : public AppMsg {
    private:
        FingerMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::finger_motion; }
        inline StringRepr to_string() const override { return "FingerMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~FingerMotionMsg() {}
    private:
        FingerMotionMsg(AppMsgArgs*);
    };

    //
    // ClipboardMsg
    //

    class ClipboardMsg final : public AppMsg {
    private:
        ClipboardMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::clipboard; }
        inline StringRepr to_string() const override { return "ClipboardMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~ClipboardMsg() {}
    private:
        ClipboardMsg(AppMsgArgs*);
    };

    //
    // DropFileMsg
    //

    class DropFileMsg final : public AppMsg {
    private:
        DropFileMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::drop_file; }
        inline StringRepr to_string() const override { return "DropFileMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~DropFileMsg() {}
    private:
        DropFileMsg(AppMsgArgs*);
    };

    //
    // DropTextMsg
    //

    class DropTextMsg final : public AppMsg {
    private:
        DropTextMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::drop_text; }
        inline StringRepr to_string() const override { return "DropTextMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~DropTextMsg() {}
    private:
        DropTextMsg(AppMsgArgs*);
    };

    // 
    // DropBeginMsg
    //

    class DropBeginMsg final : public AppMsg {
    private:
        DropBeginMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::drop_begin; }
        inline StringRepr to_string() const override { return "DropBeginMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~DropBeginMsg() {}
    private:
        DropBeginMsg(AppMsgArgs*);
    };

    //
    // DropCompleteMsg
    //

    class DropCompleteMsg final : public AppMsg {
    private:
        DropCompleteMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::drop_complete; }
        inline StringRepr to_string() const override { return "DropCompleteMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~DropCompleteMsg() {}
    private:
        DropCompleteMsg(AppMsgArgs*);
    };

    //
    // AudioDeviceAddedMsg
    //

    class AudioDeviceAddedMsg final : public AppMsg {
    private:
        AudioDeviceAddedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::audio_device_added; }
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~AudioDeviceAddedMsg() {}
    private:
        AudioDeviceAddedMsg(AppMsgArgs*);
    };

    //
    // AudioDeviceRemovedMsg
    //

    class AudioDeviceRemovedMsg final : public AppMsg {
    private:
        AudioDeviceRemovedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::audio_device_removed; }
        inline StringRepr to_string() const override { return "AudioDeviceRemovedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~AudioDeviceRemovedMsg() {}
    private:
        AudioDeviceRemovedMsg(AppMsgArgs*);
    };

    //
    // RenderTargetsResetMsg
    //

    class RenderTargetsResetMsg final : public AppMsg {
    private:
        RenderTargetsResetMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::render_targets_reset; }
        inline StringRepr to_string() const override { return "RenderTargetsResetMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~RenderTargetsResetMsg() {}
    private:
        RenderTargetsResetMsg(AppMsgArgs*);
    };

    //
    // RenderDeviceResetMsg
    //

    class RenderDeviceResetMsg final : public AppMsg {
    private:
        RenderDeviceResetMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::render_device_reset; }
        inline StringRepr to_string() const override { return "RenderDeviceResetMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~RenderDeviceResetMsg() {}
    private:
        RenderDeviceResetMsg(AppMsgArgs*);
    };






}
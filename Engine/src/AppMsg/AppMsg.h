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

    enum class AppMsgType {
         null,
         quit,
         unhandled,
         window,
         system,
         keydown,
         keyup,
         keyboard,
         text_edit,
         text_input,
         keymap_changed,
         mouse_motion,
         mouse_button_down,
         mouse_button_up,
         mouse_button,
         mouse_wheel,
         joy_axis_motion,
         joy_ball_motion,
         joy_hat_motion,
         joy_button_down,
         joy_button_up,
         joy_device_added,
         joy_device_removed,
         controller_axis_motion,
         controller_button_down,
         controller_button_up,
         controller_device_added,
         controller_device_removed,
         controller_device_remapped,
         finger_down,
         finger_up,
         finger_motion,
         clipboard,
         drop_file,
         drop_text,
         drop_begin,
         drop_complete,
         audio_device_added,
         audio_device_removed,
         render_targets_reset,
         render_device_reset,
    };

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

    // AppMsg and sub classes typedef const * const as pointer. This is the preferred point to be used
    // with these types as they should only be used in very few areas. The static create methods return a raw pointer
    // instead of the typedefd pointer because these classes use a memory manager and there is no need for them to be
    // explicitly deleted

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
        typedef const AppMsg* const ptr;
        static void destroy(AppMsgAccessKey& key, AppMsg* msg) { delete msg; }
        static void init_memory_pool(AppMsgAccessKey&);
        static void destroy_memory_pool(AppMsgAccessKey&);

        virtual const AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        inline Tick get_time_stamp() const { return _args->get_creation_time(); }
        virtual inline void set_args(AppMsgAccessKey&, AppMsgArgs* args) { _args = args; }
        inline bool is_type(const AppMsgType& type) const { return get_type() == type; }
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
        typedef const NullMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static NullMsg::ptr cast(AppMsg::ptr);

        inline StringRepr to_string() const override { return "NullMsg"; }
        inline const AppMsgType get_type() const override { return type; }
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
        typedef const QuitMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static QuitMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "QuitMsg"; }
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
        typedef const UnhandledMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static UnhandledMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "UnhandledMsg"; }
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
        typedef const WindowMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static WindowMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "WindowMsg"; }
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
        typedef const SystemMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static SystemMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "SystemMsg"; }
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
        typedef const KeyboardMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static KeyboardMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
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

    class KeydownMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        typedef const KeydownMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static KeydownMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "KeyDownMsg"; }
        inline bool is_repeat() const { return _args->is_repeat(); }
        inline Key get_key() const { return _args->get_key(); }
        inline char get_key_char() const { return _args->get_key().get_key_char(); }
        inline uint32_t get_window() const { return _args->get_window(); }
    protected:
        inline ~KeydownMsg() {}
    private:
        KeydownMsg(AppMsgArgs*);
    };

    //
    // KeyUpMsg
    //

    class KeyupMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        typedef const KeyupMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static KeyupMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "KeyUpMsg"; }
        inline bool is_repeat() const { return _args->is_repeat(); }
        inline Key get_key() const { return _args->get_key(); }
        inline char get_key_char() const { return _args->get_key().get_key_char(); }
        inline uint32_t get_window() const { return _args->get_window(); }
    protected:
        inline ~KeyupMsg() {}
    private:
        KeyupMsg(AppMsgArgs*);
    };

    //
    // TextEditMsg
    //

    class TextEditMsg final : public AppMsg {
    private:
        TextEditMsgArgs* _args;
    public:
        typedef const TextEditMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static TextEditMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "TextEditMsg"; }
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
        typedef const TextInputMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static TextInputMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "TextInputMsg"; }
    protected:
        inline ~TextInputMsg() {}
    private:
        TextInputMsg(AppMsgArgs*);
    };

    // 
    // KeyMapChangedMsg
    // 

    class KeymapChangedMsg final : public AppMsg {
    private:
        KeyMapChangedMsgArgs* _args;
    public:
        typedef const KeymapChangedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static KeymapChangedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "KeyMapChangedMsg"; }
    protected:
        inline ~KeymapChangedMsg() {}
    private:
        KeymapChangedMsg(AppMsgArgs*);
    };

    // @TODO: MouseButtonMsg instead of MouseButtonUp/DOwn
    
    //
    // MouseButtonMsg
    //
    class MouseButtonMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        typedef const MouseButtonMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static MouseButtonMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
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
        typedef const MouseButtonDownMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static MouseButtonDownMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "MouseButtonDownMsg"; }
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
        typedef const MouseButtonUpMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static MouseButtonUpMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "MouseButtonUpMsg"; }
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
        typedef const MouseMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static MouseMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
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
        typedef const MouseWheelMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static MouseWheelMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const { return type; }
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
        typedef const JoyAxisMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyAxisMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyAxisMotionMsg"; }
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
        typedef const JoyBallMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyBallMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyBallMotionMsg"; }
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
        typedef const JoyHatMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyHatMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyHatMotionMsg"; }
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
        typedef const JoyButtonDownMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyButtonDownMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyButtonDownMsg"; }
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
        typedef const JoyButtonUpMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyButtonUpMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyButtonUpMsg"; }
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
        typedef const JoyDeviceAddedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyDeviceAddedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsg"; }
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
        typedef const JoyDeviceRemovedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static JoyDeviceRemovedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "JoyDeviceRemovedMsg"; }
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
        typedef const ControllerAxisMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerAxisMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerAxisMotionMsg"; }
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
        typedef const ControllerButtonDownMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerButtonDownMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerAxisButtonMsg"; }
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
        typedef const ControllerButtonUpMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerButtonUpMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerAxisButtonUpMsg"; }
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
        typedef const ControllerDeviceAddedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerDeviceAddedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsg"; }
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
        typedef const ControllerDeviceRemovedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerDeviceRemovedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsg"; }
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
        typedef const ControllerDeviceRemappedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ControllerDeviceRemappedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ControllerDeviceRemappedMsg"; }
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
        typedef const FingerDownMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static FingerDownMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "FingerDownMsg"; }
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
        typedef const FingerUpMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static FingerUpMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "FingerUpMsg"; }
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
        typedef const FingerMotionMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static FingerMotionMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "FingerMotionMsg"; }
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
        typedef const ClipboardMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static ClipboardMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "ClipboardMsg"; }
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
        typedef const DropFileMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static DropFileMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "DropFileMsg"; }
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
        typedef const DropTextMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static DropTextMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "DropTextMsg"; }
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
        typedef const DropBeginMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static DropBeginMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "DropBeginMsg"; }
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
        typedef const DropCompleteMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static DropCompleteMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "DropCompleteMsg"; }
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
        typedef const AudioDeviceAddedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static AudioDeviceAddedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsg"; }
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
        typedef const AudioDeviceRemovedMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static AudioDeviceRemovedMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "AudioDeviceRemovedMsg"; }
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
        typedef const RenderTargetsResetMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static RenderTargetsResetMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "RenderTargetsResetMsg"; }
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
        typedef const RenderDeviceResetMsg* const ptr;
        static const AppMsgType type;
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
        static RenderDeviceResetMsg::ptr cast(AppMsg::ptr);

        inline const AppMsgType get_type() const override { return type; }
        inline StringRepr to_string() const override { return "RenderDeviceResetMsg"; }
    protected:
        inline ~RenderDeviceResetMsg() {}
    private:
        RenderDeviceResetMsg(AppMsgArgs*);
    };
}
#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        // Initialize the memory pool to one becuase there will only be one message
        // at anygiven time
        AppMsg::inititialize_memory_pool( 1 );
        _current_message = new AppMsg( 0 );
    }

    AFramework::~AFramework() {
        if ( _current_message ) {
            delete _current_message;
            _current_message = nullptr;
        }
    }

    void AFramework::main_loop() {
        Time time = 0;
        while ( _current_message->get_type() != QuitMsg::type ) {
            get_app_msg();
            frame_begin( time );
            frame_render( time );
            frame_end( time );
        }
    }
}
#include "AppMsg.h"

namespace ZeroEngine {

    AppMsgType MouseMsg::type = MOUSE_MSG;

    AppMsgType QuitMsg::type = QUIT_MSG;

    AppMsgArgs AppMsgArgs::empty = EmptyMsgArgs();
}
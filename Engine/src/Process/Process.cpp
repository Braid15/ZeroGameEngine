#include "Process.h"

namespace ZeroEngine {

    Process::Process() {
        _state = ProcessState::null;
        _child = nullptr;
    }

    Process::~Process() {
        if (_child) {
            _child->on_abort();
        }
    }

    Process::ptr Process::remove_child() {
        if (_child) {
            Process::ptr child = _child;
            _child.reset();
            return child;
        }
        return Process::ptr();
    }
}
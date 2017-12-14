#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"

namespace ZeroEngine {
    
    enum class ProcessState {
        null,
        uninitialized,
        removed,
        running,
        paused,
        succeeded,
        failed,
        aborted,
    };

    class Process : public IZeroObject {
    public:
        typedef std::shared_ptr<Process> ptr;
        typedef std::weak_ptr<Process> weak_ptr;
    private:
        friend class ProcessManager;
        ProcessState _state;
        Process::ptr _child;
    public:
        Process();
        virtual ~Process();
        inline void succeed();
        inline void fail();
        inline void pause();
        inline void resume();
        inline ProcessState get_state() const { return _state; }
        inline bool is_alive() const;
        inline bool is_dead() const;
        inline bool is_removed() const { return (_state == ProcessState::removed); }
        inline bool is_paused() const { return (_state == ProcessState::paused); }
        inline void attach_child(Process::ptr child);
        inline Process::ptr peek_child() const { return _child; }
        Process::ptr remove_child();
        virtual StringRepr to_string() const = 0;
    protected:
        virtual void on_update(Tick delta_time) = 0;
        inline virtual void on_initialize() { _state = ProcessState::running; }
        inline virtual void on_success() {}
        inline virtual void on_fail() {}
        inline virtual void on_abort() {}
    private:
        inline void set_state(ProcessState state) { _state = state; }
    };


    inline void Process::succeed() {
        assert(_state == ProcessState::running || _state == ProcessState::paused);
        _state = ProcessState::succeeded;
    }

    inline void Process::fail() {
        assert(_state == ProcessState::running || _state == ProcessState::paused);
        _state = ProcessState::failed;
    }

    inline void Process::pause() {
        if (_state == ProcessState::running) {
            _state = ProcessState::paused;
        }
    }

    inline void Process::resume() {
        if (_state == ProcessState::paused) {
            _state = ProcessState::running;
        }
    }

    inline void Process::attach_child(Process::ptr child) {
        if (_child) {
            _child->attach_child(child);
        } else {
            _child = child;
        }
    }

    inline bool Process::is_alive() const {
        return (_state == ProcessState::running || _state == ProcessState::paused);
    }

    inline bool Process::is_dead() const {
        return (_state == ProcessState::succeeded
                || _state == ProcessState::failed
                || _state == ProcessState::aborted);
    }
}
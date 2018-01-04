#include "ProcessManager.h"

namespace ZeroEngine {

    ProcessManager::~ProcessManager() {
        clear_all_processes();
    }

    // returns success count in upper 16 bits and fail count in lower 16 bits
    Uint32 ProcessManager::update_processes(Tick delta_time) {
        Uint16 success_count = 0;
        Uint16 fail_count = 0;

        ProcessList::iterator iter = _process_list.begin();
        while (iter != _process_list.end()) {
            ProcessList::iterator cur_iter = iter;
            ++iter;

            Process::ptr current_process = *cur_iter;

            if (current_process->get_state() == ProcessState::uninitialized) {
                current_process->on_initialize();
            }

            if (current_process->get_state() == ProcessState::running) {
                current_process->on_update(delta_time);
            }

            if (current_process->is_dead()) {
                switch (current_process->get_state()) {
                    case ProcessState::succeeded:
                    {
                        current_process->on_success();
                        Process::ptr child = current_process->remove_child();
                        if (child) {
                            attach_process(child);
                        } else {
                            ++success_count;
                        }
                        break;
                    }

                    case ProcessState::failed:
                    {
                        current_process->on_fail();
                        ++fail_count;
                        break;
                    }

                    case ProcessState::aborted:
                    {
                        current_process->on_abort();
                        ++fail_count;
                        break;
                    }

                    case ProcessState::null:
                    {
                        std::cout << current_process->to_string() << " is set to null state\n";
                        break;
                    }
                }

                _process_list.erase(cur_iter);
            }
        }

        return ((success_count << 16) | fail_count);
    }

    Process::weak_ptr ProcessManager::attach_process(Process::ptr process) {
        _process_list.push_front(process);
        return Process::weak_ptr(process);
    }

    void ProcessManager::abort_all_processes(bool immediate) {
        ProcessList::iterator iter = _process_list.begin();
        while (iter != _process_list.end()) {
            ProcessList::iterator cur_iter = iter;
            ++iter;

            Process::ptr process = *cur_iter;

            if (process->is_alive()) {
                process->set_state(ProcessState::aborted);
                if (immediate) {
                    process->on_abort();
                    _process_list.erase(cur_iter);
                }
            }
        }
    }

    //
    // Private members
    //
    void ProcessManager::clear_all_processes() {
        _process_list.clear();
    }
}
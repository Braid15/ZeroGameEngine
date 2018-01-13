#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "Process.h"

namespace ZeroEngine {

    class ProcessManager : public IZeroObject {
    private:
        friend class Process;
        typedef std::list<Process::ptr> ProcessList;
        ProcessList _process_list;
    public:
        ~ProcessManager();
        Uint32 update_processes(Tick delta_time);
        Process::weak_ptr attach_process(Process::ptr process);
        void abort_all_processes(bool immediate=false);
        inline Uint32 get_process_count() const;
        inline StringRepr to_string() const { return "ProcessManager"; }
    private:
        void clear_all_processes();
    };


    inline Uint32 ProcessManager::get_process_count() const {
        return static_cast<Uint32>(_process_list.size());
    }
}
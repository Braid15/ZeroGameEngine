#pragma once

#include <string>
#include <map>

#include "../AtomicTypes.h"

namespace ZeroEngine {

    // @TODO: This was thrown together quickly

    class Logger {
    private:
        static Logger* _instance;

        std::string* _debug_tag;
        std::string* _todo_tag;
        std::string* _unimplemented_tag;

        std::map<std::string, bool> _agent_map;
        std::map<std::string, bool> _tag_map;
        std::map<std::string, bool> _func_map;
    public:
        ~Logger();
        static void intialize();
        static void log_debug(std::string agent, std::string msg, std::string func);

        static void log_todo(std::string agent, std::string msg, std::string func, Int32 line);

        static void log_unimplemented(std::string file, std::string func, Int32 line);

        static void disable_tag(const char* tag);
        static void enable_tag(const char* tag);
        
        static void disable_agent(const char* agent);
        static void enable_agent(const char* agent);

        static void disable_func(const char* agent, const char* func);
        static void enable_func(const char* agent, const char* func);

        static void shutdown();
    private:
        Logger();
        std::string make_agent_func(const char* agent, const char* func);
        std::string make_agent_func(std::string agent, std::string func);
    };


// @TODO: Make it an option to specifiy how many times the msg should be printed
#define LOG_DEBUG(agent, msg)                                                               \
    {                                                                                       \
        static bool limit_reached = false;                                                  \
        static Uint32 count = 0;                                                          \
        if (!limit_reached && count++ == 0) {                                               \
            limit_reached = true;                                                           \
            Logger::log_debug(std::string(agent), std::string(msg), std::string(__func__)); \
        }                                                                                   \
    }


#define LOG_TODO(agent, msg)                                                                         \
    {                                                                                                \
        static bool limit_reached = false;                                                           \
        static Uint32 count = 0;                                                                   \
        if (!limit_reached && count++ == 0) {                                                        \
            limit_reached = true;                                                                    \
            Logger::log_todo(std::string(agent), std::string(msg), std::string(__func__), __LINE__); \
        }                                                                                            \
    }


#define LOG_UNIMPLEMENTED()                                                                    \
    {                                                                                          \
        static bool limit_reached = false;                                                     \
        static Uint32 count = 0;                                                             \
        if (!limit_reached && count++ == 0) {                                                  \
            limit_reached = true;                                                              \
            Logger::log_unimplemented(std::string(__FILE__), std::string(__func__), __LINE__); \
        }                                                                                      \
    }
}
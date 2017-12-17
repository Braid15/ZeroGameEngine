#include "Logging.h"
#include "../Memory/Memory.h"

#include <map>

// @TODO: This was thrown together quickly and all of it needs to be optimized.

namespace ZeroEngine {

    Logger* Logger::_instance = nullptr;

    Logger::Logger() {
        _debug_tag = zero_new std::string("DEBUG");
        _todo_tag = zero_new std::string("TODO");
        _unimplemented_tag = zero_new std::string("UNIMPLEMENTED");

        _tag_map[*_debug_tag] = true;
        _tag_map[*_todo_tag] = true;
        _tag_map[*_unimplemented_tag] = true;
    }

    Logger::~Logger() {
        _agent_map.clear();
        _tag_map.clear();
        _func_map.clear();

        zero_delete(_debug_tag);
        zero_delete(_todo_tag);
        zero_delete(_unimplemented_tag);
    }


    std::string Logger::make_agent_func(const char* agent, const char* func) {
        return std::string(agent) + "::" + std::string(func);
    }

    std::string Logger::make_agent_func(std::string agent, std::string func) {
        return agent + "::" + func;
    }

    void Logger::intialize() {
        if (_instance == nullptr) {
            _instance = zero_new Logger();
        }
    }

    void Logger::log_debug(std::string agent, std::string msg, std::string func) {
        #ifdef _DEBUG
        intialize();

        if (_instance->_tag_map[*_instance->_debug_tag]) {

            auto agent_iter = _instance->_agent_map.find(agent);
            if (agent_iter == _instance->_agent_map.end()) {
                _instance->_agent_map[agent] = true;
            }

            std::string agent_func = _instance->make_agent_func(agent, func);
            auto func_iter = _instance->_func_map.find(agent_func);
            if (func_iter == _instance->_func_map.end()) {
                _instance->_func_map[agent_func] = true;
            }

            if (_instance->_agent_map[agent] && _instance->_func_map[agent_func]) {
                printf("[DEBUG] [%s::%s] %s\n", agent.c_str(), func.c_str(), msg.c_str()); 
            }
        }
        #endif
    }

    void Logger::log_todo(std::string agent, std::string msg, std::string func, int line) {
        #ifdef _DEBUG
        intialize();

        if (_instance->_tag_map[*_instance->_todo_tag]) {
            auto agent_iter = _instance->_agent_map.find(agent);
            if (agent_iter == _instance->_agent_map.end()) {
                _instance->_agent_map[agent] = true;
            }

            std::string agent_func = _instance->make_agent_func(agent, func);
            auto func_iter = _instance->_func_map.find(agent_func);
            if (func_iter == _instance->_func_map.end()) {
                _instance->_func_map[agent_func] = true;
            }

            if (_instance->_agent_map[agent] && _instance->_func_map[agent_func]) {
                printf("[TODO] [%s::%s:%d] %s\n", agent.c_str(), func.c_str(), line, msg.c_str());
            }
        }
        #endif
    }

    void Logger::log_unimplemented(std::string file, std::string func, int line) {
        #ifdef _DEBUG
        intialize();
        if (_instance->_tag_map[*_instance->_unimplemented_tag]) {
            printf("[UNIMPLEMENTED] [%s::%s:%d]", file.c_str(), func.c_str(), line);
        }
        #endif
    }

    void Logger::disable_tag(const char* tag) {
        intialize();
        _instance->_tag_map[std::string(tag)] = false;
    }

    void Logger::enable_tag(const char* tag) {
        intialize();
        _instance->_tag_map[std::string(tag)] = true;
    }

    void Logger::disable_agent(const char* agent) {
        intialize();
        _instance->_agent_map[std::string(agent)] = false;
    }

    void Logger::enable_agent(const char* agent) {
        intialize();
        _instance->_agent_map[std::string(agent)] = true;
    }

    void Logger::disable_func(const char* agent, const char* func) {
        intialize();
        _instance->_func_map[_instance->make_agent_func(agent, func)] = false;
    }

    void Logger::enable_func(const char* agent, const char* func) {
        intialize();
        _instance->_func_map[_instance->make_agent_func(agent, func)] = true;
    }

    void Logger::shutdown() {
        zero_delete(_instance);
    }
}
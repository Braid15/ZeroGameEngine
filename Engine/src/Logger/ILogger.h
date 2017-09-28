#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // The methods that take in tags can be used with a config file.
    // The config file will specify whether the certain tag should be logged or not


    class ILoggable;

    // Defines the interface for Engine logging
    // This should just be used for normal logging and not debug logging.
    // Debug logging will use macros so as to use __FILE__, __func__, __LINE__
    class ILogger {

    public:
        virtual bool Initialize( const char* config_file_path ) = 0;
        virtual bool Initialize( const std::string& config_file_path ) = 0;
        virtual bool Shutdown() = 0;
        virtual bool SetLogPath( const char* file_path ) = 0;
        virtual bool SetLogPath( const std::string& file_path ) = 0;
        virtual void Log( const std::string& message ) = 0;
        virtual void Log( const char* message ) = 0;
        virtual void Log( const std::string& tag, const std::string& message ) = 0;
        virtual void Log( const char* tag, const char* message ) = 0;
        virtual void Log( const ILoggable& loggable ) = 0;
    };
}
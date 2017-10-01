#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // The methods that take in tags can be used with a config file.
    // The config file will specify whether the certain tag should be logged or not

    class Tag;
    class ILoggable;

    // Defines the interface for Engine logging
    // This should just be used for normal logging and not debug logging.
    // Debug logging will use macros so as to use __FILE__, __func__, __LINE__
    class ILogger {

    public:
        virtual bool Initialize() = 0;
        virtual bool Initialize( const char* config_file_path ) = 0;
        virtual bool Initialize( const std::string& config_file_path ) = 0;
        virtual bool Shutdown() = 0;
        virtual bool Log( const std::string* const message ) = 0;
        virtual bool Log( const std::string& message ) = 0;
        virtual bool Log( const char* message ) = 0;
        virtual bool Log( const Tag& tag, const std::string& message ) = 0;
        virtual bool Log( const Tag& tag, const char* message ) = 0;
        virtual bool Log( const ILoggable& loggable ) = 0;
    };
}
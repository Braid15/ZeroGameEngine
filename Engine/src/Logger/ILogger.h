#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // The methods that take in tags can be used with a config file.
    // The config file will specify whether the certain tag should be logged or not

    // TODO: Implement Tag class
    class Tag;
    class ILoggable;

    // Defines the interface for Engine logging
    // This should just be used for normal logging and not debug logging.
    // Debug logging will use macros so as to use __FILE__, __func__, __LINE__
    class ILogger : public IType {

    /* Public interface */
    public:
        virtual bool initialize() = 0;
        virtual bool initialize( const char* config_file_path ) = 0;
        virtual bool initialize( const std::string& config_file_path ) = 0;
        virtual bool shutdown() = 0;
        virtual bool log( const std::string& message ) const = 0;
        virtual bool log( const char* message ) const = 0;
        virtual bool log( const Tag& tag, const std::string& message ) const = 0;
        virtual bool log( const Tag& tag, const char* message ) const = 0;
        virtual bool log( const ILoggable& loggable, const char* message ) const = 0;
        virtual bool log( const ILoggable& loggable, const std::string& message ) const = 0;

    /* IType interface */
    public:
        virtual const Type get_type() const = 0;
        virtual const char* to_string() const = 0;
    };
}
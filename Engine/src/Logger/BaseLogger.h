#pragma once

#include "../ZeroEngineStd.h"
#include "ILogger.h"

namespace ZeroEngine {

    class BaseLogger : ILogger {

    /* BaseLogger interface */
    public:
        BaseLogger();
        BaseLogger( const char* file_name );
        BaseLogger( const std::string& file_name );
        virtual ~BaseLogger();

    /* ILogger interface */
    public:
        virtual bool Initialize();
        virtual bool Initialize( const char* config_file_path ) override;
        virtual bool Initialize( const std::string& config_file_path ) override;
        virtual bool Shutdown() override;
        // TEMP const?
        virtual bool Log( const std::string* const message ) override;
        virtual bool Log( const std::string& message ) override;
        virtual bool Log( const char* message ) override;
        virtual bool Log( const Tag& tag, const std::string& message ) override;
        virtual bool Log( const Tag& tag, const char* message ) override;
        virtual bool Log( const ILoggable& loggable ) override;

    /* Fields */
    private:
        const std::string* _log_file_path;

    /* Instance methods */
    private:
        const std::string _get_default_file_name();
        const std::string _get_default_log_path();
        bool _write_line_to_file( const std::string& message, bool overwrite ) const;

    /* Unit Test */
    public:
        static void _UNIT_TEST_();
    };
}
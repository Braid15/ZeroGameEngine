#pragma once

#include "../ZeroEngineStd.h"
#include "ILogger.h"

namespace ZeroEngine {

    class BaseLogger : public ILogger {

    /* BaseLogger interface */
    public:
        BaseLogger();
        BaseLogger( const char* file_name );
        BaseLogger( const std::string& file_name );
        virtual ~BaseLogger();

    /* ILogger interface */
    public:
        virtual bool initialize() override;
        virtual bool initialize( const char* config_file_path ) override;
        virtual bool initialize( const std::string& config_file_path ) override;
        virtual bool shutdown() override;
        virtual bool log( const std::string& message ) const override;
        virtual bool log( const char* message ) const override;
        virtual bool log( const Tag& tag, const std::string& message ) const override;
        virtual bool log( const Tag& tag, const char* message ) const override;
        virtual bool log( const ILoggable& loggable, const char* message ) const override;
        virtual bool log( const ILoggable& loggable, const std::string& message ) const override;

    /* IType interface */
    public:
        virtual const Type get_type() const override { return _THIS; }
        virtual const char* to_string() const override { return "BaseLogger"; }

    /* Fields */
    private:
        const std::string* _log_file_path;

    /* Instance methods */
    private:
        const std::string _get_default_file_name() const;
        const std::string _get_default_log_path() const;
        bool _write_line_to_file( const std::string& message, bool overwrite ) const;

    /* Unit Test */
    public:
        static void _UNIT_TEST_();
    };
}
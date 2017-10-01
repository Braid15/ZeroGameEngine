#pragma once

#include "../ZeroEngineStd.h"
#include "ILogger.h"

namespace ZeroEngine {

    // TODO: NEed to add a map and function to toggle which types should be logged
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
        virtual bool log( const IType& type, const std::string& message ) const override;
        virtual bool log( const IType& type, const char* message ) const override;
        virtual bool log( const ILoggable& loggable, const char* message ) const override;
        virtual bool log( const ILoggable& loggable, const std::string& message ) const override;

    /* IType interface */
    public:
        virtual const TypeID get_type() const override { return _THIS; }
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
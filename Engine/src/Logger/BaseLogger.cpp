#include "BaseLogger.h"

namespace ZeroEngine {

    /* BaseLogger interface */

    BaseLogger::BaseLogger() {
        _log_file_path = new std::string( _get_default_log_path() + _get_default_file_name() );
    }

    BaseLogger::BaseLogger( const char* file_name ) {
        _log_file_path = new std::string( _get_default_log_path() + std::string( file_name ) );
    }

    BaseLogger::BaseLogger( const std::string& file_name ) {
        _log_file_path = new std::string( _get_default_log_path() + file_name );
    }

    BaseLogger::~BaseLogger() {
        delete _log_file_path;
        _log_file_path = nullptr;
    }


    /* ILogger interface */

    bool BaseLogger::initialize() {
        bool success = false;
        // Overwrite previous log file
        success = _write_line_to_file( "Logger initialized", true );
        return success;
    }

    bool BaseLogger::initialize( const char* config_file_path ) {
        bool success = false;
        // Overwrite previous log file
        success = _write_line_to_file( "Logger initialized", true );
        return success;
    }

    bool BaseLogger::initialize( const std::string& config_file_path ) {
        bool success = false;
        // Overwrite previous log file
        success = _write_line_to_file( "Logger initialized", true );
        return success;
    }

    bool BaseLogger::shutdown() {
        return true;
    }

    bool BaseLogger::log( const std::string& message ) const {
        return _write_line_to_file( message, false );
    }

    bool BaseLogger::log( const char* message ) const {
        return _write_line_to_file( std::string( message ), false );
    }

    bool BaseLogger::log( const IType& type, const std::string& message ) const {
        return _write_line_to_file( std::string( type.get_type() ) + " - " + message, false );
    }

    bool BaseLogger::log( const IType& type, const char* message ) const {
        return _write_line_to_file( std::string( type.get_type() ) + " - " + 
            std::string( message ), false );
    }

    bool BaseLogger::log( const ILoggable& loggable, const char* message ) const {
        return _write_line_to_file( "ILOGGABLE const char*", false );
    }

    bool BaseLogger::log( const ILoggable& loggable, const std::string& message ) const {
        return _write_line_to_file( "ILOGGABLE - const std::string&", false );
    }


    /* Instance methods */

    const std::string BaseLogger::_get_default_file_name() const {
        #ifdef _DEBUG
        std::string configuration = "D";
        #else
        std::string configuration;
        #endif

        #ifdef _X86
        std::string platform = "X86";
        #else
        std::string platform = "X64";
        #endif

        std::string sep = "_";
        std::string file_name = "ZeroEngine" + sep + platform + sep + configuration + ".log";

        return file_name;
    }

    const std::string BaseLogger::_get_default_log_path() const {
        // TODO: Need to put application root in main app class
        return std::string( "S://projects//game-engines//zerogameengine//engine//log//" );
    }

    bool BaseLogger::_write_line_to_file( const std::string& message, bool overwrite ) const {
        bool success = false;
        std::ofstream file;
        if ( overwrite ) {
            file.open( _log_file_path->c_str() );
        } else {
            file.open( _log_file_path->c_str(), std::ios::in | std::ios::ate ); 
        }
        if ( file.is_open() ) {
            file << message << "\n";
            file.close();
            success = true;
        }
        return success;
    }


    /* Unit Test */
    void BaseLogger::_UNIT_TEST_() {
        BaseLogger logger;
        if ( logger.initialize() ) {
            logger.log( "LOG MESSAGE" );
            logger.log( std::string( "LOG MESSAGE 2" ) );
        } else {
            std::cout << "Logger was unable to initialize" << std::endl;
        }
    }
}

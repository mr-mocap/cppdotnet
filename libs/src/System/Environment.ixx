module;

export module System:Environment;

import System:Exception;
import <tuple>;
import <cstring>;
import <stdlib.h>;
#if __cpp_lib_stacktrace > 202011L
#include <stacktrace>
#endif

#include "System/Collections/Specialized/StringDictionary.hpp"
export import <string>;
export import <string_view>;
import <map>;

namespace System
{

export
class Environment final
{
public:

    static std::string_view GetEnvironmentVariable(const char *var_name);
    static std::string_view GetEnvironmentVariable(std::string_view var_name);

    static void SetEnvironmentVariable(const char *var_name, const char *value);

    static Collections::Specialized::StringDictionary GetEnvironmentVariables();

    static std::string ExpandEnvironmentVariables(std::string_view input);

    constexpr static std::string_view NewLine()
    {
        return "\n"; // TODO: Make correct under other OSs
    }

    static std::string StackTrace();

    [[noreturn]] static void Exit(int exit_code);
};

}

namespace System
{

// Enclosing Reference Marker(s), Variable Name
using EnvironmentVariableReference = std::tuple<std::string_view, std::string_view>;

export
{

static std::string_view ContainsSurroundingTokens(std::string_view input,
                                                  std::string_view start_token,
                                                  std::string_view end_token)
{
    std::string_view::size_type start_pos = input.find(start_token);

    if ( start_pos == std::string_view::npos )
        return {}; // Not found
    
    std::string_view::size_type end_pos = input.find(end_token, start_pos + 1);

    if ( end_pos == std::string_view::npos)
        return input.substr( start_pos );
    
    return input.substr( start_pos, end_pos );
}

static EnvironmentVariableReference ContainsEnvironmentVariableReference(std::string_view input)
{
    if ( !input.empty() )
    {
        std::string_view begin_enclosed{ "${" };
        std::string_view end_enclosed{ "}" };

        if (std::string_view found = ContainsSurroundingTokens(input, begin_enclosed, end_enclosed); !found.empty())
            return std::make_tuple( found, found.substr(
                                                         begin_enclosed.size(),
                                                         found.size() - ( begin_enclosed.size() + end_enclosed.size() )
                                                       ) );

        if (std::string_view::size_type found_marker = input.find('$'); found_marker != std::string_view::npos)
        {
            auto one_past_end = input.find_first_not_of( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_", found_marker );

            if ( one_past_end == std::string_view::npos )
            {
                // All the way to the end
                std::string_view sub{ input.substr( found_marker ) };

                return std::make_tuple( sub, sub.substr( 1 ) );
            }

            return std::make_tuple(
                                    input.substr( found_marker, one_past_end - found_marker ),
                                    input.substr( found_marker + 1, one_past_end - found_marker )
                                  );
        }
    }
    return std::make_tuple( std::string_view{}, std::string_view{} );
}

std::string_view Environment::GetEnvironmentVariable(const char *var_name)
{
    if ( !var_name )
        ThrowWithTarget( ArgumentNullException{ "variable" } );

    auto result = std::getenv( var_name );

    if ( result )
        return std::string_view{ result, std::strlen(result) };
    
    return {};
}

std::string_view Environment::GetEnvironmentVariable(std::string_view var_name)
{
    return GetEnvironmentVariable( std::string{ var_name }.c_str() );
}

void Environment::SetEnvironmentVariable(const char *variable, const char *value)
{
    if ( !variable )
        ThrowWithTarget( ArgumentNullException{ "variable" } );

    if ( std::strlen(variable) == 0 )
        ThrowWithTarget( ArgumentException{ "variable" } );

    if ( std::strchr(variable, '=') )
        ThrowWithTarget( ArgumentException{ "variable" } );

    if ( variable && (std::strlen(variable) > 0) )
    {
        if ( !value || (std::strlen(value) == 0) )
        {
            // Unset the variable
            unsetenv( variable );
        }
        else
        {
            int result = setenv( variable, value, true );

            UNUSED(result);
            // result == 0 is success, -1 is error
        }
    }
}

std::string Environment::ExpandEnvironmentVariables(std::string_view input)
{
    if ( input.empty() )
        ThrowWithTarget( ArgumentNullException{ "input" } );

    std::string return_value{ input };

    while ( true )
    {
        auto [substitution, var_name] = ContainsEnvironmentVariableReference(return_value);

        if ( var_name.empty() )
            break;
        
        substitution = GetEnvironmentVariable( std::string{var_name} );
    }
    return return_value;
}

Collections::Specialized::StringDictionary Environment::GetEnvironmentVariables()
{
    std::unordered_map<std::string, std::string> retval;

    // "environ" is a UNIX standard (POSIX?) variable containing the process environment variables
    for (char **current_variable = environ; current_variable; ++current_variable)
    {
        char *current_variable_ptr = *current_variable;

        // Are we at the end of the array?
        if ( !current_variable_ptr)
            break;

        char *separator = std::strpbrk( current_variable_ptr, "=" );

        if ( !separator )
            break;
        
        size_t length = separator - current_variable_ptr;
        std::string name{ current_variable_ptr, length };
        std::string value{ separator + 1, strlen(separator + 1) };

        retval[ name ] = value;
    }
    return retval;
}

std::string Environment::StackTrace()
{
#if __cpp_lib_stacktrace > 202011L
    return std::stacktrace::current().to_string();
#else
    return "System::Environment::Callstack() (not compiled under C++23 or greater with stacktrace library)";
#endif
}

void Environment::Exit(int exit_code)
{
    std::exit( exit_code );
}

}

}
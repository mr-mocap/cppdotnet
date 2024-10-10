#include "System/Environment.hpp"
#include "System/Exception.hpp"
#include <tuple>
#include <cstring>
#include <stdlib.h>


namespace System
{

// Enclosing Reference Marker(s), Variable Name
using EnvironmentVariableReference = std::tuple<std::string_view, std::string_view>;

static std::string_view ContainsSurroundingTokens(const std::string_view input,
                                                  const std::string_view start_token,
                                                  const std::string_view end_token)
{
    std::string_view::size_type start_pos = input.find(start_token);

    if ( start_pos == std::string_view::npos )
        return {}; // Not found
    
    std::string_view::size_type end_pos = input.find(end_token, start_pos + 1);

    if ( end_pos == std::string_view::npos)
        return input.substr( start_pos );
    
    return input.substr( start_pos, end_pos );
}

static EnvironmentVariableReference ContainsEnvironmentVariableReference(const std::string_view input)
{
    using namespace std::literals;

    if ( !input.empty() )
    {
        std::string_view begin_enclosed{ "${"sv };
        std::string_view end_enclosed{ "}"sv };

        if (std::string_view found = ContainsSurroundingTokens(input, begin_enclosed, end_enclosed); !found.empty())
            return std::make_tuple( found, found.substr(
                                                         begin_enclosed.size(),
                                                         found.size() - ( begin_enclosed.size() + end_enclosed.size() )
                                                       ) );

        if (std::string_view::size_type found_marker = input.find('$'); found_marker != std::string_view::npos)
        {
            auto one_past_end = input.find_first_not_of( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"sv, found_marker );

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

const std::string_view Environment::GetEnvironmentVariable(const char *var_name)
{
    using namespace std::literals;

    if ( !var_name )
        ThrowWithTarget( ArgumentNullException{ "variable"sv } );

    auto result = std::getenv( var_name );

    if ( result )
        return std::string_view{ result, std::strlen(result) };
    
    return {};
}

const std::string_view Environment::GetEnvironmentVariable(const std::string_view var_name)
{
    return GetEnvironmentVariable( std::string{ var_name }.c_str() );
}

void Environment::SetEnvironmentVariable(const char *variable, const char *value)
{
    using namespace std::literals;

    if ( !variable )
        ThrowWithTarget( ArgumentNullException{ "variable"sv } );

    if ( std::strlen(variable) == 0 )
        ThrowWithTarget( ArgumentException{ "variable"sv } );

    if ( std::strchr(variable, '=') )
        ThrowWithTarget( ArgumentException{ "variable"sv } );

    if ( variable && (std::strlen(variable) > 0) )
    {
        if ( !value || (std::strlen(value) == 0) )
        {
            // Unset the variable
            unsetenv( variable );
        }
        else
        {
            auto result = setenv( variable, value, true );

            // result == 0 is success, -1 is error
        }
    }
}

std::string Environment::ExpandEnvironmentVariables(const std::string_view input)
{
    using namespace std::literals;

    if ( input.empty() )
        ThrowWithTarget( ArgumentNullException{ "input"sv } );

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

std::map<std::string, std::string> Environment::GetEnvironmentVariables()
{
    std::map<std::string, std::string> retval;

    for (char **current_variable = environ; current_variable; ++current_variable)
    {
        // Are we at the end of the array?
        if ( !*current_variable)
            break;

        char *separator = std::strpbrk( *current_variable, "=" );

        if ( !separator )
            break;
        
        std::string name{ *current_variable, separator - *current_variable };
        std::string value{ separator + 1, strlen(separator + 1) };

        retval[ name ] = value;
    }
    return retval;
}

const std::string_view Environment::NewLine()
{
    using namespace std::literals;

    return "\n"sv;
}

void Environment::Exit(int exit_code)
{
    std::exit( exit_code );
}

}
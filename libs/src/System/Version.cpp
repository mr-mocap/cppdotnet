#include "System/Version.hpp"
#include "System/Exception.hpp"
#include "System/Convert.hpp"
#include "System/Text/StringBuilder.hpp"
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <format>


namespace System
{

static std::vector<int> Append(std::vector<int> &&input, const std::vector<int> &other)
{
    for (int i : other)
        input.push_back( i );
    return std::move(input);
}

static std::vector<int> ToInts(std::string_view input, const char separator = '.')
{
    auto pos = input.find_first_of( separator );

    if ( pos == std::string_view::npos )
    {
        std::string s{ input };
        int converted_value = std::atoi( s.c_str() );

        return { converted_value };
    }

    std::string s{ input.substr( 0, pos ) };
    int converted_value = std::atoi( s.c_str() );

    input.remove_prefix( pos + 1 );
    if ( input.empty() )
        return std::vector<int>(1, converted_value);

    return Append( std::vector<int>(1, converted_value), ToInts(input) );
}

Version::Version(const std::string_view input)
{
    Version result{ Parse( input ) };

    *this = result;
}

Version Version::Parse(const std::string_view input)
{
    std::vector<int> values{ ToInts(input) };

    if ( values.size() > 3)
        return Version( values[0], values[1], values[2], values[3] );
    if ( values.size() > 2)
        return Version( values[0], values[1], values[2] );
    if ( values.size() > 1)
        return Version( values[0], values[1] );
    
    Version result;

    result._major = values[0];
    return result;
}

std::string Version::ToString() const
{
    Text::StringBuilder result;

    result.Append( Major() ).Append('.').Append( Minor() );

    if ( Build() != -1 )
        result.Append('.').Append( Build() );

    if ( Revision() != -1 )
        result.Append('.').Append( Revision() );
    
    return result;
}

std::string Version::ToString(int field_count) const
{
    using namespace std::literals;

    if ( (field_count < 0) || (field_count > 4) )
        ThrowWithTarget( ArgumentOutOfRangeException{ "field_count"sv } );
    
    if ( field_count == 0 )
        return {};

    if ( field_count == 1 )
        return Convert::ToChars( Major() );

    if ( field_count == 2 )
        return Text::StringBuilder().Append( Major() ).Append('.').Append( Minor() );

    if ( field_count == 3 )
    {
        if ( Build() == -1 )
            ThrowWithTarget( ArgumentOutOfRangeException{ "field_count"sv, "Build() is not set"sv } );

        return Text::StringBuilder().Append( Major() ).Append('.')
                                    .Append( Minor() ).Append('.')
                                    .Append( Build() );
    }

    if ( field_count == 4 )
    {
        if ( Revision() == -1 )
            ThrowWithTarget( ArgumentOutOfRangeException{ "field_count"sv, "Revision() is not set"sv } );

        return Text::StringBuilder().Append( Major() ).Append('.')
                                    .Append( Minor() ).Append('.')
                                    .Append( Build() ).Append('.')
                                    .Append( Revision() );
    }

    return {};
}

}
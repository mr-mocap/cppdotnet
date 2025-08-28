module;

export module System:Version;

import System:Exception;
import System:Convert;
export import <string>;
export import <string_view>;
import <vector>;
import <cstring>;
import <cstdlib>;


namespace System
{

export
class Version final
{
public:
    Version() = default;
    Version(int major, int minor, int build, int revision)
        :
        _major{ major },
        _minor{ minor },
        _build{ build },
        _revision{ revision }
    {
    }
    Version(int major, int minor, int build)
        :
        _major{ major },
        _minor{ minor },
        _build{ build }
    {
    }
    Version(int major, int minor)
        :
        _major{ major },
        _minor{ minor }
    {
    }
    Version(std::string_view input);
    Version(const Version &other) = default;

    int Major() const { return _major; }
    int Minor() const { return _minor; }
    int Build() const { return _build; }
    int Revision() const { return _revision; }

    static Version Parse(std::string_view input);

    std::string ToString() const;
    std::string ToString(int field_count) const;

    Version &operator =(const Version &other) = default;
protected:
    int _major = 0;
    int _minor = 0;
    int _build = -1;
    int _revision = -1;
};

}


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

Version::Version(std::string_view input)
{
    Version result{ Parse( input ) };

    *this = result;
}

Version Version::Parse(std::string_view input)
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
#if 0
    Text::StringBuilder result;

    result.Append( Major() ).Append('.').Append( Minor() );

    if ( Build() != -1 )
        result.Append('.').Append( Build() );

    if ( Revision() != -1 )
        result.Append('.').Append( Revision() );
    
    return result;
#else
    return {};
#endif
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
#if 0
        return Text::StringBuilder().Append( Major() ).Append('.').Append( Minor() );
#else
        return {};
#endif

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
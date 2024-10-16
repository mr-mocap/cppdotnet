#include "TestEnum.hpp"
#include "System/Enum.hpp"
#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <limits>
#include <string>

using namespace std::literals;

namespace TestEnum
{

class MyTraceLevel : public System::Enum<MyTraceLevel, int>
{
public:
    using BaseType   = System::Enum<MyTraceLevel, int>;

    using BaseType::value_type;
    using value_array_type = typename std::array<value_type, 5>;
    using name_array_type  = std::array<const std::string_view, 5>;
    using name_value_map_type = typename std::map<const std::string_view, value_type>;

    enum Values : value_type {
        Off = 0,
        Error,
        Warning,
        Info,
        Verbose
    };
    
    explicit MyTraceLevel(Values v = Values::Off) : Enum( v ) { }

    static size_t ValueCount() { return _values.size(); }
    static size_t NameCount()  { return _names.size(); }

    const std::span<const std::string_view> GetNames() const
    {
        return std::span( _names );
    }

    const std::span<value_type> GetValues() const
    {
        return std::span( _values );
    }

    static const std::string_view GetName(Values value)
    {
        for (auto &[k, v] : _name_value_map)
            if ( v == value )
                return k;

        return {};
    }

    static bool IsDefined(value_type value)
    {
        return std::ranges::find( _values, value ) != _values.end();
    }

    static bool IsDefined(const std::string_view name)
    {
        return std::ranges::find( _names, name ) != _names.end();
    }

    MyTraceLevel &operator =(Values v)
    {
        BaseType::operator =(v);
        return *this;
    }

    static value_type Parse(const std::string_view string_value)
    {
        if ( string_value.empty() )
            ThrowWithTarget( System::ArgumentException{ "Argument is empty", "value" } );

        if ( !IsDefined(string_value) )
            ThrowWithTarget( System::ArgumentException{ "Argument does not name a defined constant", "value" } );

        // First, check for a name...
        for (auto &[k, v] : _name_value_map)
            if ( k == string_value )
                return v;
        
        int converted;

        // We don't have a name, so let's convert to an integer type...
        try
        {
            converted = std::stoi( std::string{string_value} );
        }
        catch(const std::invalid_argument &e)
        {
            ThrowWithTarget( System::ArgumentException{ "Argument does not contain Enumeration information", "string_value" } );
        }
        catch(const std::out_of_range &e)
        {
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "string_value" } );
        }

        // And don't forget to check if it can be represented in the value_type!

        if ( converted < std::numeric_limits<value_type>::min() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "string_value", "Converted value is less than the minimum for this type" } );
        if ( converted > std::numeric_limits<value_type>::max() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{ "string_value", "Converted value is greater than the maximum for this type" } );

        return static_cast<value_type>(converted);
    }

protected:

    static name_value_map_type _name_value_map;
    static value_array_type    _values;
    static name_array_type     _names;
};

MyTraceLevel::value_array_type    MyTraceLevel::_values{ Off, Error, Warning, Info, Verbose };
MyTraceLevel::name_array_type     MyTraceLevel::_names{ "Off", "Error", "Warning", "Info", "Verbose" };
MyTraceLevel::name_value_map_type MyTraceLevel::_name_value_map{
    { "Off", Off },
    { "Error", Error },
    { "Warning", Warning },
    { "Info", Info },
    { "Verbose", Verbose }
};


void CheckGetNames()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    std::cout << "GetNames() = \n";
    std::ranges::copy( t.GetNames(), std::ostream_iterator<const std::string_view>(std::cout, "\t") );
    std::cout << std::endl;
}

void CheckGetValues()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    std::cout << "GetValues() = \n";
    std::ranges::copy( t.GetValues(), std::ostream_iterator<MyTraceLevel::value_type>(std::cout, "\t") );
    std::cout << std::endl;
}

void IsDefined()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    assert( t.IsDefined( MyTraceLevel::Off ) );
    assert( t.IsDefined( MyTraceLevel::Error ) );
    assert( t.IsDefined( MyTraceLevel::Warning ) );
    assert( t.IsDefined( MyTraceLevel::Info ) );
    assert( t.IsDefined( MyTraceLevel::Verbose ) );
    assert( !t.IsDefined( 92 ) );

    assert( t.IsDefined( "Off" ) );
    assert( t.IsDefined( "Error"sv ) );
    assert( t.IsDefined( "Warning"sv ) );
    assert( t.IsDefined( "Info"sv ) );
    assert( t.IsDefined( "Verbose"sv ) );
    assert( !t.IsDefined( "Fail"sv ) );
}

void GetName()
{
    std::cout << __func__ << std::endl;

    assert( MyTraceLevel::GetName( MyTraceLevel::Off ) == "Off" );
    assert( MyTraceLevel::GetName( MyTraceLevel::Error ) == "Error" );
    assert( MyTraceLevel::GetName( MyTraceLevel::Warning ) == "Warning" );
    assert( MyTraceLevel::GetName( MyTraceLevel::Info ) == "Info" );
    assert( MyTraceLevel::GetName( MyTraceLevel::Verbose ) == "Verbose" );
}

void Parse()
{
    std::cout << __func__ << std::endl;

    try
    {
        assert( MyTraceLevel::Parse("Off"sv) == MyTraceLevel::Off );
        assert( MyTraceLevel::Parse("Error") == MyTraceLevel::Error );
        assert( MyTraceLevel::Parse("Warning") == MyTraceLevel::Warning );
        assert( MyTraceLevel::Parse("Info") == MyTraceLevel::Info );
        assert( MyTraceLevel::Parse("Verbose") == MyTraceLevel::Verbose );
    }
    catch (const std::exception& e)
    {
        assert(false);
    }

    try
    {
        MyTraceLevel::Parse("Fail");
    }
    catch (const System::ArgumentException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
}

void Construct()
{
    std::cout << __func__ << std::endl;

    {
        MyTraceLevel t;

        assert( t == 0 );
    }

    {
        MyTraceLevel t{ MyTraceLevel::Off };

        assert( t == MyTraceLevel::Off );
    }

    {
        MyTraceLevel t{ MyTraceLevel::Error };

        assert( t == MyTraceLevel::Error );
    }

    {
        MyTraceLevel t{ MyTraceLevel::Warning };

        assert( t == MyTraceLevel::Warning );
    }

    {
        MyTraceLevel t{ MyTraceLevel::Info };

        assert( t == MyTraceLevel::Info );
    }

    {
        MyTraceLevel t{ MyTraceLevel::Verbose };

        assert( t == MyTraceLevel::Verbose );
    }
}

void OperatorEquals()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    assert( t == 0 );

    t = MyTraceLevel::Error;

    assert( t == MyTraceLevel::Error );
}

void Run()
{
    std::cout << "Running Enum Tests..." << std::endl;

    CheckGetNames();
    CheckGetValues();
    IsDefined();
    GetName();
    Parse();
    Construct();
    OperatorEquals();

    std::cout << "PASSED!" << std::endl;
}

}
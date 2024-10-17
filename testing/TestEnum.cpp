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

    enum Values : value_type {
        Off = 0,
        Error,
        Warning,
        Info,
        Verbose
    };
    
    using value_array_type = typename std::array<value_type, 5>;
    using name_array_type  = std::array<std::string_view, 5>;
    using name_value_pair_type  = std::pair<const char *, enum Values>;
    using name_value_array_type = std::array<name_value_pair_type, 5>;

    explicit MyTraceLevel(Values v = Values::Off) : Enum( v ) { }

    static const std::span<const std::string_view> GetNames()
    {
        static const name_array_type names{ MakeNames() };

        return std::span( names );
    }

    static const std::span<const value_type> GetValues()
    {
        static const value_array_type values{ MakeValues() };

        return std::span( values );
    }

    static const std::string_view GetName(Values value)
    {
        auto found = std::ranges::find( _name_value_array,
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == _name_value_array.end() )
            return {};

        return found->first;
    }

    const std::string_view GetName() const
    {
        return GetName( static_cast<Values>(_currentValue) );
    }

    static bool IsDefined(value_type value)
    {
        return std::ranges::find( GetValues(), value ) != GetValues().end();
    }

    static bool IsDefined(const std::string_view name)
    {
        return std::ranges::find( GetNames(), name ) != GetNames().end();
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
        for (const name_value_pair_type &i : _name_value_array)
            if ( i.first == string_value )
                return i.second;
        
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

        if ( !IsDefined( static_cast<value_type>(converted) ) )
            return {};

        return static_cast<value_type>(converted);
    }

    static std::optional<value_type> TryParse(const std::string_view string_value)
    {
        // First, check for a name...
        for (const name_value_pair_type &i : _name_value_array)
            if ( i.first == string_value )
                return i.second;
        
        int converted;

        // We don't have a name, so let's convert to an integer type...
        try
        {
            converted = std::stoi( std::string{string_value} );
        }
        catch(const std::invalid_argument &e)
        {
            return {};
        }
        catch(const std::out_of_range &e)
        {
            return {};
        }
        
        // And don't forget to check if it can be represented in the value_type!

        if ( converted < std::numeric_limits<value_type>::min() )
            return {};
        if ( converted > std::numeric_limits<value_type>::max() )
            return {};

        // Return the value, even if it is NOT within the list of values!
        return std::optional<value_type>{ static_cast<value_type>(converted) };
    }
protected:

    static name_array_type  MakeNames()
    {
        name_array_type array;

        std::ranges::transform( _name_value_array, array.begin(), [](const auto &i) { return i.first; } );
        return array;
    }

    static value_array_type MakeValues()
    {
        value_array_type array;

        std::ranges::transform( _name_value_array, array.begin(), [](const auto &i) { return i.second; } );
        return array;
    }

    static const name_value_array_type _name_value_array;
};

const MyTraceLevel::name_value_array_type MyTraceLevel::_name_value_array{ {
    { "Off",     MyTraceLevel::Off     },
    { "Error",   MyTraceLevel::Error   },
    { "Warning", MyTraceLevel::Warning },
    { "Info",    MyTraceLevel::Info    },
    { "Verbose", MyTraceLevel::Verbose }
} };


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

    // Empty string when value not in GetValues()
    assert( MyTraceLevel::GetName( static_cast<MyTraceLevel::Values>(MyTraceLevel::Verbose + 10) ).empty() );
    assert( MyTraceLevel::GetName( static_cast<MyTraceLevel::Values>(-1) ).empty() );

    MyTraceLevel t{ MyTraceLevel::Error };

    assert( t.GetName() == "Error" );
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

void TryParse()
{
    std::cout << __func__ << std::endl;

    // Success... using names
    assert( MyTraceLevel::TryParse("Off") && (MyTraceLevel::TryParse("Off").value() == MyTraceLevel::Off) );
    assert( MyTraceLevel::TryParse("Error") && (MyTraceLevel::TryParse("Error").value() == MyTraceLevel::Error) );
    assert( MyTraceLevel::TryParse("Warning") && (MyTraceLevel::TryParse("Warning").value() == MyTraceLevel::Warning) );
    assert( MyTraceLevel::TryParse("Info") && (MyTraceLevel::TryParse("Info").value() == MyTraceLevel::Info) );
    assert( MyTraceLevel::TryParse("Verbose") && (MyTraceLevel::TryParse("Verbose").value() == MyTraceLevel::Verbose) );

    // Success... using string representation of values
    assert( MyTraceLevel::TryParse("0") && (MyTraceLevel::TryParse("0").value() == MyTraceLevel::Off) );
    assert( MyTraceLevel::TryParse("1") && (MyTraceLevel::TryParse("1").value() == MyTraceLevel::Error) );
    assert( MyTraceLevel::TryParse("2") && (MyTraceLevel::TryParse("2").value() == MyTraceLevel::Warning) );
    assert( MyTraceLevel::TryParse("3") && (MyTraceLevel::TryParse("3").value() == MyTraceLevel::Info) );
    assert( MyTraceLevel::TryParse("4") && (MyTraceLevel::TryParse("4").value() == MyTraceLevel::Verbose) );

    // Failure... using name that isn't in the enumeration
    assert( !MyTraceLevel::TryParse("SomeRandomString") );

    // Failure... using number that isn't in the values
    assert( MyTraceLevel::TryParse("-1").value() == -1 );
    assert( MyTraceLevel::TryParse("5").value() == 5 );
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

void GenericEnum()
{
    std::cout << __func__ << std::endl;
#if 0
    System::Enum t;

    std::cout << "GetNames() = \n";
    std::ranges::copy( t.GetNames(), std::ostream_iterator<const std::string_view>(std::cout, "\t") );
    std::cout << std::endl;
#endif
}

void Run()
{
    std::cout << "Running Enum Tests..." << std::endl;

    CheckGetNames();
    CheckGetValues();
    IsDefined();
    GetName();
    Parse();
    TryParse();
    Construct();
    OperatorEquals();

    std::cout << "PASSED!" << std::endl;
}

}
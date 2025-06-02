#include "TestEnum.hpp"
#include "System/Enum.hpp"
#include <iostream>
#include <array>
#include <map>
#include <iterator>
#include <cassert>
#include <limits>
#include <string>
#include <type_traits>

using namespace std::literals;

namespace TestEnum
{

enum Values {
        Off = 0,
        Error,
        Warning,
        Info,
        Verbose
};


#if 0
class MyTraceLevel : public System::Enum<MyTraceLevel>
{
public:
#if 1
    enum Values : value_type {
        Off = 0,
        Error,
        Warning,
        Info,
        Verbose
    };
#else
    using Values = TestEnum::Values;
    using enum Values;
#endif

    using BaseType         = System::Enum<MyTraceLevel, int>;
    using value_array_type = typename std::array<value_type, 5>;
    using name_array_type  = std::array<std::string_view, 5>;
    using name_value_pair_type  = std::pair<const char *, Values>;
    using name_value_array_type = std::array<name_value_pair_type, 5>;

    MyTraceLevel(Values v = Values::Off) : Enum( static_cast<value_type>(v) ) { }

    friend class System::Enum<MyTraceLevel, int>;
protected:

    static const name_value_array_type _name_value_array;
};

const MyTraceLevel::name_value_array_type MyTraceLevel::_name_value_array{ {
    { "Off",     MyTraceLevel::Off     },
    { "Error",   MyTraceLevel::Error   },
    { "Warning", MyTraceLevel::Warning },
    { "Info",    MyTraceLevel::Info    },
    { "Verbose", MyTraceLevel::Verbose }
} };
#else
class MyTraceLevelPolicy
{
public:
    enum Values {
        Off = 0,
        Error,
        Warning,
        Info,
        Verbose
    };

    using value_type = enum Values;
    using underlying_type = std::underlying_type_t<value_type>;
    using name_array_type = std::array<std::string_view, 5>;
    using value_array_type = std::array<value_type, 5>;
    using underlying_value_array_type = std::array<underlying_type, 5>;
    using name_value_pair_type = std::pair<const char *, value_type>;

protected:

    static std::span<name_value_pair_type> NameValueArray()
    {
        static name_value_pair_type array[] = {
            { "Off",     Off     },
            { "Error",   Error   },
            { "Warning", Warning },
            { "Info",    Info    },
            { "Verbose", Verbose }
        };

        return std::span( array );
    }
};

using MyTraceLevel = System::Enum<MyTraceLevelPolicy>;
#endif


void CheckGetNames()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    std::cout << "GetNames() =\t";
    std::ranges::copy( t.GetNames(), std::ostream_iterator<std::string_view>(std::cout, "\t") );
    std::cout << std::endl;
}

void CheckGetValues()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    std::cout << "GetValues() =\t";
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
    assert( t.IsDefined( "Error" ) );
    assert( t.IsDefined( "Warning" ) );
    assert( t.IsDefined( "Info" ) );
    assert( t.IsDefined( "Verbose" ) );
    assert( !t.IsDefined( "Fail" ) );
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
        assert( MyTraceLevel::Parse("Off") == MyTraceLevel::Off );
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
    assert( !MyTraceLevel::TryParse("-1") );
    assert( !MyTraceLevel::TryParse("5") );
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

void Assignment()
{
    std::cout << __func__ << std::endl;

    MyTraceLevel t;

    assert( t == 0 );

    t = MyTraceLevel::Error;

    assert( t == MyTraceLevel::Error );
}

void GetValuesAsUnderlyingType()
{
    std::cout << __func__ << std::endl;

    auto array{ MyTraceLevel::GetValuesAsUnderlyingType() };

    assert( array[0] == 0 );
    assert( array[1] == 1 );
    assert( array[2] == 2 );
    assert( array[3] == 3 );
    assert( array[4] == 4 );
}

void GetTypeCode()
{
    std::cout << __func__ << std::endl;

    assert( MyTraceLevel{}.GetTypeCode() == System::TypeCode::UInt32 );
}

void GenericEnum()
{
    std::cout << __func__ << std::endl;
#if 0
    System::Enum t;

    std::cout << "GetNames() = \n";
    std::ranges::copy( t.GetNames(), std::ostream_iterator<std::string_view>(std::cout, "\t") );
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
    Assignment();
    GetValuesAsUnderlyingType();
    GetTypeCode();

    std::cout << "PASSED!" << std::endl;
}

}
#include <cppdotnet/System/Collections/Specialized/StringDictionary.hpp>
#include <cstdlib>
#include <cassert>

namespace TestStringDictionary
{

void DefaultConstruction()
{
    System::Collections::Specialized::StringDictionary d;

    assert( d.Count() == 0 );
}

void ConstructWithInitializerList()
{
    // Directly
    System::Collections::Specialized::StringDictionary d
    {
        {"b", "1"},
        {"c", "2"},
        {"a", "3"},
        {"d", "4"}
    };

    // Should be in the same order
    assert( d.Count() == 4 );
    assert( d["b"] == "1" );
    assert( d["c"] == "2" );
    assert( d["a"] == "3" );
    assert( d["d"] == "4" );
}

void ConstructWithMap()
{
    // From a std::map
    {
        std::unordered_map<std::string, std::string> m{ { {"b", "1"}, {"c", "2"}, {"a", "3"}, {"d", "4"} } };

        assert( m.size() == 4 );
        assert( m["b"] == "1" );
        assert( m["c"] == "2" );
        assert( m["a"] == "3" );
        assert( m["d"] == "4" );

        // Directly
        System::Collections::Specialized::StringDictionary d( m );

        // Should have the same keys with the same values...
        assert( d.Count() == 4 );
        assert( d["b"] == "1" );
        assert( d["c"] == "2" );
        assert( d["a"] == "3" );
        assert( d["d"] == "4" );
    }

    // Test construction with an rvalue
    {
        std::unordered_map<std::string, std::string> m{ { {"b", "1"}, {"c", "2"}, {"a", "3"}, {"d", "4"} } };

        assert( m.size() == 4 );
        assert( m["b"] == "1" );
        assert( m["c"] == "2" );
        assert( m["a"] == "3" );
        assert( m["d"] == "4" );

        // Using an rvalue std::map
        System::Collections::Specialized::StringDictionary d( std::unordered_map<std::string, std::string>( { { "a", "1" },
                                                                                                              { "b", "2" },
                                                                                                              { "c", "3" },
                                                                                                              { "d", "4" } } ) );

        // Should be in the same order
        assert( d.Count() == 4 );
        assert( d["a"] == "1" );
        assert( d["b"] == "2" );
        assert( d["c"] == "3" );
        assert( d["d"] == "4" );
    }

    // Test construction with a begin()/end() iterator pair...
    {
        std::pair<std::string, std::string> array[] = { {"a", "2"}, {"b", "4"}, {"c", "6"} };

        System::Collections::Specialized::StringDictionary d{ std::begin(array), std::end(array) };

        // Should be in the same order
        assert( d.Count() == 3 );
        assert( d["a"] == "2" );
        assert( d["b"] == "4" );
        assert( d["c"] == "6" );
    }

    // Test construction with a deduction guide...
    {
        std::unordered_map<std::string, std::string> m{ {"a", "1"}, {"b", "2"}, {"c", "3"} };

        System::Collections::Specialized::StringDictionary d{ m };

        // Should be in the same order
        assert( d.Count() == 3 );
        assert( d["a"] == "1" );
        assert( d["b"] == "2" );
        assert( d["c"] == "3" );
    }
}

void HasHeterogenousLookup()
{
    System::Collections::Specialized::StringDictionary d
    {
        {"b", "1"},
        {"c", "2"},
        {"a", "3"},
        {"d", "4"}
    };

    std::string_view v = "c";
    const char *ccp = "d";

    assert( d[v]   == "2" );
    assert( d[ccp] == "4" ); // This should really call d.operator [](std::string_view)

    assert( d.at(v)   == "2" );
    assert( d.at(ccp) == "4" );

    assert( d.ContainsKey(v) );
    assert( d.ContainsKey(ccp) );
    assert( !d.ContainsKey("Test") ); // Remember "Test" for later...

    {
        std::string result;

        assert( d.TryGetValue(v, result) );
        assert( result == "2" );

        assert( d.TryGetValue(ccp, result) );
        assert( result == "4" );
    }

    d.Add( std::string_view("Test"), std::string_view("v") );
    
    assert( d.ContainsKey( std::string_view("Test") ) );
}

void ContainsValueCanHandleEquivalentStringTypes()
{
    // I expect that the templated versions will be called
    // in all cases except for an exact std::string input parameter.

    System::Collections::Specialized::StringDictionary d
    {
        {"b", "1"},
        {"c", "2"},
        {"a", "3"},
        {"d", "4"}
    };

    assert( d.ContainsValue( "4" ) );
    assert( !d.ContainsValue( "99" ) );

    assert( d.ContainsValue( std::string_view("3") ) );
    assert( !d.ContainsValue( std::string_view("99") ) );

    assert( d.ContainsValue( std::string("2") ) );
    assert( !d.ContainsValue( std::string("99") ) );
}

void Run()
{
    DefaultConstruction();
    ConstructWithInitializerList();
    ConstructWithMap();
    HasHeterogenousLookup();
    ContainsValueCanHandleEquivalentStringTypes();
}

}

int main(void)
{
    TestStringDictionary::Run();

    return EXIT_SUCCESS;
}
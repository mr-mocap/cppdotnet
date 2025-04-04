#include "TestDictionary.hpp"
#include "System/Collections/Generic/Dictionary.hpp"
#include "System/Console.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>


namespace TestDictionary
{

void DefaultConstruction()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    assert( d.Count() == 0 );
}

void ConstructWithInitializerList()
{
    std::cout << __func__ << std::endl;

    // Directly
    System::Collections::Generic::Dictionary<std::string, int> d
    {
        {"b", 1},
        {"c", 2},
        {"a", 3},
        {"d", 4}
    };

    // Should be in the same order
    assert( d.Count() == 4 );
    assert( d["b"] == 1 );
    assert( d["c"] == 2 );
    assert( d["a"] == 3 );
    assert( d["d"] == 4 );
}

void ConstructWithMap()
{
    std::cout << __func__ << std::endl;

    // From a std::map
    {
        std::map<std::string, int> m{ { {"b", 1}, {"c", 2}, {"a", 3}, {"d", 4} } };

        assert( m.size() == 4 );
        assert( m["b"] == 1 );
        assert( m["c"] == 2 );
        assert( m["a"] == 3 );
        assert( m["d"] == 4 );

        // Directly
        System::Collections::Generic::Dictionary<std::string, int> d( m );

        // Should be in the same order
        assert( d.Count() == 4 );
        assert( d["b"] == 1 );
        assert( d["c"] == 2 );
        assert( d["a"] == 3 );
        assert( d["d"] == 4 );
    }

    // From std::map using a specialized Comparison operator
    {
        std::map<std::string, int, std::greater<std::string>> m{ { {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4} } };

        for (auto [key, value] : m)
            std::cout << "key: " << key << "\tvalue: " << value << std::endl;

        // Verify that the items are in reverse order...
        assert( m.size() == 4 );
        assert( std::next(m.begin(), 0)->first == "d" );
        assert( std::next(m.begin(), 1)->first == "c" );
        assert( std::next(m.begin(), 2)->first == "b" );
        assert( std::next(m.begin(), 3)->first == "a" );

        // With a pair of iterators...
        System::Collections::Generic::Dictionary<std::string, int> d( m.begin(), m.end() );

        // Verify it is in < ordering (opposite from the std::map above, because we used the default Comparison)
        assert( d.Count() == 4 );

        // access like a std::pair
        assert( std::next(d.begin(), 0)->first == "a" );
        assert( std::next(d.begin(), 1)->first == "b" );
        assert( std::next(d.begin(), 2)->first == "c" );
        assert( std::next(d.begin(), 3)->first == "d" );

        // access like a KeyValuePair
        assert( std::next(d.begin(), 0)->Key() == "a" );
        assert( std::next(d.begin(), 0)->Value() == 1 );

        assert( std::next(d.begin(), 1)->Key() == "b" );
        assert( std::next(d.begin(), 1)->Value() == 2 );

        assert( std::next(d.begin(), 2)->Key() == "c" );
        assert( std::next(d.begin(), 2)->Value() == 3 );

        assert( std::next(d.begin(), 3)->Key() == "d" );
        assert( std::next(d.begin(), 3)->Value() == 4 );
    }

    // Test construction with an rvalue
    {
        std::map<std::string, int> m{ { {"b", 1}, {"c", 2}, {"a", 3}, {"d", 4} } };

        assert( m.size() == 4 );
        assert( m["b"] == 1 );
        assert( m["c"] == 2 );
        assert( m["a"] == 3 );
        assert( m["d"] == 4 );

        // Using an rvalue std::map
        System::Collections::Generic::Dictionary<std::string, int> d( std::map<std::string, int>( { { "a", 1 },
                                                                                                    { "b", 2 },
                                                                                                    { "c", 3 },
                                                                                                    { "d", 4 } } ) );

        // Should be in the same order
        assert( d.Count() == 4 );
        assert( d["a"] == 1 );
        assert( d["b"] == 2 );
        assert( d["c"] == 3 );
        assert( d["d"] == 4 );
    }

    // Test construction with a begin()/end() iterator pair...
    {
        std::pair<std::string, int> array[] = { {"a", 2}, {"b", 4}, {"c", 6} };

        System::Collections::Generic::Dictionary<std::string, int> d{ std::begin(array), std::end(array) };

        // Should be in the same order
        assert( d.Count() == 3 );
        assert( d["a"] == 2 );
        assert( d["b"] == 4 );
        assert( d["c"] == 6 );
    }

    // Test construction with a deduction guide...
    {
        std::map<std::string, int> m{ {"a", 1}, {"b", 2}, {"c", 3} };

        System::Collections::Generic::Dictionary d{ m };

        // Should be in the same order
        assert( d.Count() == 3 );
        assert( d["a"] == 1 );
        assert( d["b"] == 2 );
        assert( d["c"] == 3 );
    }
}

void AddAddsNonexistingKey()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    assert( d.Count() == 0 );

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );
}

void AddKeyThrowsExceptionWhenAddingIdenticalKey()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    try
    {
        d.Add("one", 1);
        assert( false );
    }
    catch(const System::ArgumentException &e)
    {
        std::cout << e.ToString() << std::endl;
        assert( true );
    }
}

void ClearClearsAllItemsInDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    d.Clear();

    assert( d.Count() == 0 );
}

void ContainsKeyReturnsFalseWhenKeyIsNotInDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    assert( !d.ContainsKey("two") );
}

void ContainsKeyReturnsTrueWhenKeyIsInDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    assert( d.ContainsKey("one") );
}

void ContainsValueReturnsFalseWhenValueIsNotInDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    assert( !d.ContainsValue(12) );
}

void ContainsValueReturnsTrueWhenValueIsInDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.Count() == 1 );
    assert( d["one"] == 1 );

    assert( d.ContainsValue(1) );
}

void RemoveReturnsTrueIfKeyIsRemoved()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.ContainsKey("one") );

    bool result = d.Remove("one");

    assert( result == true );
    assert( !d.ContainsKey("one") );
}

void RemoveReturnsFalseIfKeyIsNotRemoved()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);

    assert( d.ContainsKey("one") );
    assert( d.Count() == 1 );
    assert( !d.ContainsKey("two") );

    bool result = d.Remove("two");

    assert( result == false );
    
    // Unchanged Dictionary
    assert( d.ContainsKey("one") );
    assert( d.Count() == 1 );
    assert( !d.ContainsKey("two") );
}

void TryGetValueReturnsTrueAndSetsValueIfKeyIsFound()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;
    int retrieved_value = 0;

    d.Add("one", 1);

    assert( d.ContainsKey("one") );
    assert( retrieved_value == 0 );

    bool result = d.TryGetValue("one", retrieved_value);

    assert( result == true );
    assert( retrieved_value == 1 );
}

void TryGetValueReturnsFalseAndSetsValueToDefaultIfKeyIsNotFound()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;
    int retrieved_value = -1;

    d.Add("one", 1);

    assert( retrieved_value == -1 );
    assert( !d.ContainsKey("two") );

    bool result = d.TryGetValue("two", retrieved_value);

    assert( result == false );
    assert( retrieved_value == int{} );
}

void KeysReturnsTheKeysInTheDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    d.Add("one", 1);
    d.Add("two", 2);
    d.Add("three", 3);

    assert( d.ContainsKey("one") );
    assert( d.ContainsKey("two") );
    assert( d.ContainsKey("three") );
    assert( d.Count() == 3 );

    System::Collections::Generic::Dictionary<std::string, int>::KeyCollection kc;

    assert( kc.Count() == 0 );

    kc = d.Keys();

    assert( kc.Count() == d.Count() );
    assert( kc.Count() == 3 );
    assert( kc.Contains("one") );
    assert( kc.Contains("two") );
    assert( kc.Contains("three") );
}

void IteratingAsKeyValuePair()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d
    {
        {"a", 1},
        {"b", 2},
        {"c", 3},
        {"d", 4}
    };

    // As underlying type...
    for (const std::pair<const std::string, int> &iCurrent : d)
        std::cout << "pair [" << iCurrent.first << ", " << iCurrent.second << "]" << std::endl;

    // Entire object...
    for (const System::Collections::Generic::KeyValuePair<std::string, int> &iCurrent : d)
        std::cout << iCurrent.ToString() << std::endl;

    // Underlying type...
    for (const auto &iCurrent : d)
        std::cout << "pair [" << iCurrent.first << ", " << iCurrent.second << "]" << std::endl;

    // Backward...
    System::Console::Out().WriteLine("Backwards...");
    for (const auto &iCurrent : d | std::views::reverse)
        System::Console::Out().WriteLine("{}", iCurrent.ToString());
}

void Run()
{
    std::cout << "Running Dictionary Tests..." << std::endl;

    DefaultConstruction();
    ConstructWithInitializerList();
    ConstructWithMap();
    AddAddsNonexistingKey();
    AddKeyThrowsExceptionWhenAddingIdenticalKey();
    ClearClearsAllItemsInDictionary();
    ContainsKeyReturnsFalseWhenKeyIsNotInDictionary();
    ContainsKeyReturnsTrueWhenKeyIsInDictionary();
    ContainsValueReturnsFalseWhenValueIsNotInDictionary();
    ContainsValueReturnsTrueWhenValueIsInDictionary();
    RemoveReturnsTrueIfKeyIsRemoved();
    RemoveReturnsFalseIfKeyIsNotRemoved();
    TryGetValueReturnsTrueAndSetsValueIfKeyIsFound();
    TryGetValueReturnsFalseAndSetsValueToDefaultIfKeyIsNotFound();
    KeysReturnsTheKeysInTheDictionary();
    IteratingAsKeyValuePair();

    std::cout << "PASSED!" << std::endl;
}

}
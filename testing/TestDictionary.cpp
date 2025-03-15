#include "TestDictionary.hpp"
#include "System/Collections/Generic/Dictionary.hpp"
#include <iostream>
#include <cassert>


namespace TestDictionary
{

void DefaultConstruction()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<std::string, int> d;

    assert( d.Count() == 0 );
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

void Run()
{
    std::cout << "Running Dictionary Tests..." << std::endl;

    DefaultConstruction();
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

    std::cout << "PASSED!" << std::endl;
}

}
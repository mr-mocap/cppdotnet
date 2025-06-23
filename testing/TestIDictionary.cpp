#include "TestIDictionary.hpp"
#include "System/Collections/Generic/IDictionary.hpp"
#include "System/Collections/Generic/Dictionary.hpp"
#include <iostream>
#include <cassert>


namespace TestIDictionary
{

template<class K, class V>
using KVP = System::Collections::Generic::KeyValuePair<K, V>;

using DictionaryType = System::Collections::Generic::Dictionary<int, std::string>;
using IDictionaryType = System::Collections::Generic::Dictionary<int, std::string>;

System::Collections::Generic::IDictionary<int,int> TestMoveFromDictionary()
{
   System::Collections::Generic::Dictionary<int, int> example; 

   example.Add(0, 1);
   example.Add(1, 2);
   example.Add(2, 3);
   example.Add(3, 4);

   return example;
}

void MoveConstructedWithDataType()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::IDictionary<int, std::string> empty{ DictionaryType() };

    assert( empty.Count() == 0 );
}

void ConstructedWithObjectMakesANewCopy()
{
    std::cout << __func__ << std::endl;

    std::unique_ptr<DictionaryType> dictionary = std::make_unique<DictionaryType>();

    dictionary->Add(1, "one");
    dictionary->Add(2, "two");
    dictionary->Add(3, "three");

    assert( dictionary->Count() == 3 );
    assert( dictionary->Contains( KVP<int, std::string>(1, "one") ) );
    assert( dictionary->Contains( KVP<int, std::string>(2, "two") ) );
    assert( dictionary->Contains( KVP<int, std::string>(3, "three") ) );

    System::Collections::Generic::IDictionary<int, std::string> idictionary(*dictionary);

    assert( idictionary.Count() == 3 );
    assert( idictionary.Contains( KVP<int, std::string>(1, "one") ) );
    assert( idictionary.Contains( KVP<int, std::string>(2, "two") ) );
    assert( idictionary.Contains( KVP<int, std::string>(3, "three") ) );

    // Now, let's delete the original LinkedList object
    dictionary.reset();

    assert( idictionary.Count() == 3 );
    assert( idictionary.Contains( KVP<int, std::string>(1, "one") ) );
    assert( idictionary.Contains( KVP<int, std::string>(2, "two") ) );
    assert( idictionary.Contains( KVP<int, std::string>(3, "three") ) );
}

void CopyConstructorMakesANewObject()
{
    std::cout << __func__ << std::endl;

    std::unique_ptr<DictionaryType> dictionary = std::make_unique<DictionaryType>();

    dictionary->Add(1, "one");
    dictionary->Add(2, "two");
    dictionary->Add(3, "three");

    assert( dictionary->Count() == 3 );
    assert( dictionary->Contains( KVP<int, std::string>(1, "one") ) );
    assert( dictionary->Contains( KVP<int, std::string>(2, "two") ) );
    assert( dictionary->Contains( KVP<int, std::string>(3, "three") ) );

    std::unique_ptr<DictionaryType> icollection = std::make_unique<DictionaryType>(*dictionary);

    assert( icollection->Count() == 3 );
    assert( icollection->Contains( KVP<int, std::string>(1, "one") ) );
    assert( icollection->Contains( KVP<int, std::string>(2, "two") ) );
    assert( icollection->Contains( KVP<int, std::string>(3, "three") ) );

    // Now, let's delete the original LinkedList object
    dictionary.reset();

    // Check that the ICollection contains the data
    assert( icollection->Count() == 3 );
    assert( icollection->Contains( KVP<int, std::string>(1, "one") ) );
    assert( icollection->Contains( KVP<int, std::string>(2, "two") ) );
    assert( icollection->Contains( KVP<int, std::string>(3, "three") ) );

    DictionaryType icollection_copy( *icollection );

    assert( icollection_copy.Count() == 3 );
    assert( icollection_copy.Contains( KVP<int, std::string>(1, "one") ) );
    assert( icollection_copy.Contains( KVP<int, std::string>(2, "two") ) );
    assert( icollection_copy.Contains( KVP<int, std::string>(3, "three") ) );

    // Delete the original ICollection
    icollection.reset();

    // Verify that the copy hass the data
    assert( icollection_copy.Count() == 3 );
    assert( icollection_copy.Contains( KVP<int, std::string>(1, "one") ) );
    assert( icollection_copy.Contains( KVP<int, std::string>(2, "two") ) );
    assert( icollection_copy.Contains( KVP<int, std::string>(3, "three") ) );
}

void MoveConstructorLeavesOldObjectEmpty()
{
    std::cout << __func__ << std::endl;

    DictionaryType  dictionary;

    dictionary.Add(1, "one");
    dictionary.Add(2, "two");
    dictionary.Add(3, "three");

    assert( dictionary.Count() == 3 );
    assert( dictionary.Contains( KVP<int, std::string>(1, "one") ) );
    assert( dictionary.Contains( KVP<int, std::string>(2, "two") ) );
    assert( dictionary.Contains( KVP<int, std::string>(3, "three") ) );

    IDictionaryType idictionary( dictionary );

    assert( idictionary.Count() == 3 );
    assert( idictionary.Contains( KVP<int, std::string>(1, "one") ) );
    assert( idictionary.Contains( KVP<int, std::string>(2, "two") ) );
    assert( idictionary.Contains( KVP<int, std::string>(3, "three") ) );

    IDictionaryType idictionary_move( std::move(idictionary) );

    assert( idictionary_move.Count() == 3 );
    assert( idictionary_move.Contains( KVP<int, std::string>(1, "one") ) );
    assert( idictionary_move.Contains( KVP<int, std::string>(2, "two") ) );
    assert( idictionary_move.Contains( KVP<int, std::string>(3, "three") ) );

    assert( idictionary.Count() == 0 );
}

void MovedFromFunctionAsDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::IDictionary<int, int> data = TestMoveFromDictionary();

    assert( data.Count() == 4 );
    assert( data.Contains( KVP<int, int>(0, 1) ) );
    assert( data.Contains( KVP<int, int>(1, 2) ) );
    assert( data.Contains( KVP<int, int>(2, 3) ) );
    assert( data.Contains( KVP<int, int>(3, 4) ) );
}

void IterateOverDictionary()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::Dictionary<int, std::string> dictionary( { {0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"} });

    {
        System::Collections::Generic::IDictionary idictionary{ dictionary };

        for (const System::Collections::Generic::KeyValuePair<int, std::string> &i: idictionary)
        {
            std::cout << "KeyValuePair<int, string> = " << i.Key() << ", " << i.Value() << std::endl;
        }
    }
}

void Run()
{
    std::cout << "Running IDictionary Tests..." << std::endl;

    MoveConstructedWithDataType();
    ConstructedWithObjectMakesANewCopy();
    CopyConstructorMakesANewObject();
    MoveConstructorLeavesOldObjectEmpty();
    MovedFromFunctionAsDictionary();

#if 0
    ConstructWithLinkedListRef();
    ConstructWithListRef();

    IterateOverList();
    IterateOverLinkedList();
#endif
    IterateOverDictionary();

    std::cout << "PASSED!" << std::endl;
}

}
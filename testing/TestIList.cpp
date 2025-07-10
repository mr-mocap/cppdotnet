#include "TestIList.hpp"
#include "System/Collections/Generic/IList.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Collections/Generic/OrderedDictionary.hpp"
#include "System/Console.hpp"
#include <cassert>
#include <ranges>
#include <string>


namespace TestIList
{

void MoveConstructedWithDataType()
{
    System::Console::WriteLine(__func__);

    System::Collections::Generic::IList<int> empty{ System::Collections::Generic::List<int>() };

    assert( empty.Count() == 0 );
}

void ConstructedWithObjectMakesANewCopy()
{
    System::Console::WriteLine(__func__);

    System::Collections::Generic::List<int> list;

    list.Add(1);
    list.Add(2);
    list.Add(3);

    assert( list.Count() == 3 );
    assert( list.Contains(1) );
    assert( list.Contains(2) );
    assert( list.Contains(3) );

    System::Collections::Generic::IList<int> ilist( list );

    assert( ilist.Count() == 3 );
    assert( ilist.Contains(1) );
    assert( ilist.Contains(2) );
    assert( ilist.Contains(3) );

    // Now, let's delete the original object
    list.Clear();

    assert( ilist.Count() == 3 );
    assert( ilist.Contains(1) );
    assert( ilist.Contains(2) );
    assert( ilist.Contains(3) );
}

void CopyConstructorMakesANewObject()
{
    System::Console::WriteLine(__func__);

    System::Collections::Generic::List<int> list;

    list.Add(1);
    list.Add(2);
    list.Add(3);

    assert( list.Count() == 3 );
    assert( list.Contains(1) );
    assert( list.Contains(2) );
    assert( list.Contains(3) );

    System::Collections::Generic::IList<int> ilist( list );

    assert( ilist.Count() == 3 );
    assert( ilist.Contains(1) );
    assert( ilist.Contains(2) );
    assert( ilist.Contains(3) );

    // Now, let's delete the original LinkedList object
    list.Clear();

    // Check that the ilist contains the data
    assert( ilist.Count() == 3 );
    assert( ilist.Contains(1) );
    assert( ilist.Contains(2) );
    assert( ilist.Contains(3) );

    System::Collections::Generic::IList ilist_copy( ilist );

    assert( ilist_copy.Count() == 3 );
    assert( ilist_copy.Contains(1) );
    assert( ilist_copy.Contains(2) );
    assert( ilist_copy.Contains(3) );

    // Delete the original ilist
    ilist.Clear();

    // Verify that the copy hass the data
    assert( ilist_copy.Count() == 3 );
    assert( ilist_copy.Contains(1) );
    assert( ilist_copy.Contains(2) );
    assert( ilist_copy.Contains(3) );
}

void MoveConstructorLeavesOldObjectEmpty()
{
    System::Console::WriteLine(__func__);

    System::Collections::Generic::List<int>  list;

    list.Add(1);
    list.Add(2);
    list.Add(3);

    assert( list.Count() == 3 );
    assert( list.Contains(1) );
    assert( list.Contains(2) );
    assert( list.Contains(3) );

    System::Collections::Generic::IList<int> ilist( list );

    assert( ilist.Count() == 3 );
    assert( ilist.Contains(1) );
    assert( ilist.Contains(2) );
    assert( ilist.Contains(3) );

    System::Collections::Generic::IList<int> ilist_move( std::move(ilist) );

    assert( ilist_move.Count() == 3 );
    assert( ilist_move.Contains(1) );
    assert( ilist_move.Contains(2) );
    assert( ilist_move.Contains(3) );

    assert( ilist.Count() == 0 );
}

void ConstructWithListRef()
{
    System::Console::WriteLine(__func__);

    int example_data[] = { 1, 2, 3 };
    System::Collections::Generic::List<int>  list(example_data);

    assert( list.Count() == 3 );
    assert( list.Contains(1) );
    assert( list.Contains(2) );
    assert( list.Contains(3) );

    System::Collections::Generic::IListRef<int> ilistref(&list);

    assert( ilistref.Count() == 3 );
    assert( ilistref.Contains(1) );
    assert( ilistref.Contains(2) );
    assert( ilistref.Contains(3) );
}

void IterateOverListAsIList()
{
    System::Console::WriteLine(__func__);

    // Iterate Over List...
    System::Console::WriteLine("Iterating over List...");
    {
        System::Collections::Generic::List<std::string> list( {"zero", "one", "two", "three"} );
        System::Collections::Generic::IList ilist{ list };

        for (const std::string &i : ilist)
        {
            System::Console::WriteLine("string = {}", i);
        }
    }
    // Iterate Over Sorted Dictionary...
    System::Console::WriteLine("Iterating over SortedDictionary...");
    {
        System::Collections::Generic::OrderedDictionary<int, std::string> list( { {2, "two"}, {0, "zero"}, {3, "three"}, {1, "one"} } );
        System::Collections::Generic::IList ilist{ list };

        for (const System::Collections::Generic::KeyValuePair<int, std::string> &i : ilist)
        {
            System::Console::WriteLine("pair = {}: {}", i.Key(), i.Value());
        }

        // Now, let's iterate over the indices
        for (std::size_t i = 0; i < ilist.Count(); ++i)
        {
            System::Console::WriteLine("pair[{}] = {}: {}", i, ilist[i].Key(), ilist[i].Value());
        }
    }
}

void Run()
{
    System::Console::WriteLine("Running IList Tests...");

    MoveConstructedWithDataType();
    ConstructedWithObjectMakesANewCopy();
    CopyConstructorMakesANewObject();
    MoveConstructorLeavesOldObjectEmpty();

    ConstructWithListRef();
    IterateOverListAsIList();

    System::Console::WriteLine("PASSED!");
}

}
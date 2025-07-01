#include "TestIList.hpp"
#include "System/Collections/Generic/IList.hpp"
#include "System/Collections/Generic/List.hpp"
#include <iostream>
#include <cassert>


namespace TestIList
{

void MoveConstructedWithDataType()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::IList<int> empty{ System::Collections::Generic::List<int>() };

    assert( empty.Count() == 0 );
}

void ConstructedWithObjectMakesANewCopy()
{
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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

void Run()
{
    std::cout << "Running IList Tests..." << std::endl;

    MoveConstructedWithDataType();
    ConstructedWithObjectMakesANewCopy();
    CopyConstructorMakesANewObject();
    MoveConstructorLeavesOldObjectEmpty();

    ConstructWithListRef();
    //IterateOverList();

    std::cout << "PASSED!" << std::endl;
}

}
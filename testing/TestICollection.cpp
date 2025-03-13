#include "TestICollection.hpp"
#include "System/Collections/Generic/ICollection.hpp"
#include "System/Collections/Generic/LinkedList.hpp"
#include "System/Collections/Generic/List.hpp"
#include <iostream>
#include <cassert>


namespace TestICollection
{

System::Collections::Generic::ICollection<int> TestMove()
{
   System::Collections::Generic::LinkedList<int> example; 

   example.Add(1);
   example.Add(2);
   example.Add(3);
   example.Add(4);

   return example;
}

void MoveConstructedWithDataType()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::ICollection<int> empty{ System::Collections::Generic::LinkedList<int>() };

    assert( empty.Count() == 0 );
}

void ConstructWithLinkedListObject()
{
    std::cout << __func__ << std::endl;

    int example_data[] = { 1, 2, 3 };
    System::Collections::Generic::LinkedList<int>  linked_list(example_data);

    assert( linked_list.Count() == 3 );
    assert( linked_list.Contains(1) );
    assert( linked_list.Contains(2) );
    assert( linked_list.Contains(3) );

    System::Collections::Generic::ICollection<int> icollection(linked_list);

    assert( icollection.Count() == 3 );
    assert( icollection.Contains(1) );
    assert( icollection.Contains(2) );
    assert( icollection.Contains(3) );
}

void ConstructedWithObjectMakesANewCopy()
{
    std::cout << __func__ << std::endl;

    std::unique_ptr<System::Collections::Generic::LinkedList<int>> linked_list = std::make_unique<System::Collections::Generic::LinkedList<int>>();

    linked_list->Add(1);
    linked_list->Add(2);
    linked_list->Add(3);

    assert( linked_list->Count() == 3 );
    assert( linked_list->Contains(1) );
    assert( linked_list->Contains(2) );
    assert( linked_list->Contains(3) );

    System::Collections::Generic::ICollection<int> icollection(*linked_list);

    assert( icollection.Count() == 3 );
    assert( icollection.Contains(1) );
    assert( icollection.Contains(2) );
    assert( icollection.Contains(3) );

    // Now, let's delete the original LinkedList object
    linked_list.reset();

    assert( icollection.Count() == 3 );
    assert( icollection.Contains(1) );
    assert( icollection.Contains(2) );
    assert( icollection.Contains(3) );
}

void CopyConstructorMakesANewObject()
{
    std::cout << __func__ << std::endl;

    std::unique_ptr<System::Collections::Generic::LinkedList<int>> linked_list = std::make_unique<System::Collections::Generic::LinkedList<int>>();

    linked_list->Add(1);
    linked_list->Add(2);
    linked_list->Add(3);

    assert( linked_list->Count() == 3 );
    assert( linked_list->Contains(1) );
    assert( linked_list->Contains(2) );
    assert( linked_list->Contains(3) );

    std::unique_ptr<System::Collections::Generic::LinkedList<int>> icollection = std::make_unique<System::Collections::Generic::LinkedList<int>>(*linked_list);

    assert( icollection->Count() == 3 );
    assert( icollection->Contains(1) );
    assert( icollection->Contains(2) );
    assert( icollection->Contains(3) );

    // Now, let's delete the original LinkedList object
    linked_list.reset();

    // Check that the ICollection contains the data
    assert( icollection->Count() == 3 );
    assert( icollection->Contains(1) );
    assert( icollection->Contains(2) );
    assert( icollection->Contains(3) );

    System::Collections::Generic::LinkedList icollection_copy( *icollection );

    assert( icollection_copy.Count() == 3 );
    assert( icollection_copy.Contains(1) );
    assert( icollection_copy.Contains(2) );
    assert( icollection_copy.Contains(3) );

    // Delete the original ICollection
    icollection.reset();

    // Verify that the copy hass the data
    assert( icollection_copy.Count() == 3 );
    assert( icollection_copy.Contains(1) );
    assert( icollection_copy.Contains(2) );
    assert( icollection_copy.Contains(3) );
}

void MoveConstructorLeavesOldObjectEmpty()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::LinkedList<int>  linked_list;

    linked_list.Add(1);
    linked_list.Add(2);
    linked_list.Add(3);

    assert( linked_list.Count() == 3 );
    assert( linked_list.Contains(1) );
    assert( linked_list.Contains(2) );
    assert( linked_list.Contains(3) );

    System::Collections::Generic::ICollection<int> icollection( linked_list );

    assert( icollection.Count() == 3 );
    assert( icollection.Contains(1) );
    assert( icollection.Contains(2) );
    assert( icollection.Contains(3) );

    System::Collections::Generic::ICollection<int> icollection_move( std::move(icollection) );

    assert( icollection_move.Count() == 3 );
    assert( icollection_move.Contains(1) );
    assert( icollection_move.Contains(2) );
    assert( icollection_move.Contains(3) );

    assert( icollection.Count() == 0 );
}

void MovedFromFunction()
{
    std::cout << __func__ << std::endl;

    System::Collections::Generic::ICollection<int> data = TestMove();

    assert( data.Count() == 4 );
    assert( data.Contains(1) );
    assert( data.Contains(2) );
    assert( data.Contains(3) );
    assert( data.Contains(4) );
}

void Run()
{
    std::cout << "Running ICollection Tests..." << std::endl;

    MoveConstructedWithDataType();
    ConstructWithLinkedListObject();
    ConstructedWithObjectMakesANewCopy();
    CopyConstructorMakesANewObject();
    MoveConstructorLeavesOldObjectEmpty();
    MovedFromFunction();

    std::cout << "PASSED!" << std::endl;
}

}
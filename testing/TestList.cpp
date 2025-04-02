#include "TestList.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Collections/Generic/LinkedList.hpp"
#include "System/Collections/Generic/ICollection.hpp"
#include <iostream>
#include <cassert>
#include <array>


using namespace System;

namespace TestList
{

void DefaultConstructsToEmpty()
{
    std::cout << __func__ << std::endl;

    Collections::Generic::List<int> empty_list;

    assert( empty_list.Count() == 0 );
}

void ConstructWithExternalSequence()
{
    std::cout << __func__ << std::endl;

    // From built-in array
    {
        int a[] = { 1, 2, 3 };
        Collections::Generic::List<int> list( a );

        assert( a[0] == 1 );
        assert( a[1] == 2 );
        assert( a[2] == 3 );

        assert( list.Count() == 3 );
        assert( list[0] == 1 );
        assert( list[1] == 2 );
        assert( list[2] == 3 );
    }

    // From std array
    {
        std::array<int, 3> a{ 1, 2, 3 };
        Collections::Generic::List<int> list( std::begin(a), std::end(a) );

        assert( a[0] == 1 );
        assert( a[1] == 2 );
        assert( a[2] == 3 );

        assert( list.Count() == 3 );
        assert( list[0] == 1 );
        assert( list[1] == 2 );
        assert( list[2] == 3 );
    }

    // From initializer_list
    {
        Collections::Generic::List<int> list( { 1, 2, 3 } );

        assert( list.Count() == 3 );
        assert( list[0] == 1 );
        assert( list[1] == 2 );
        assert( list[2] == 3 );
    }
}

void ClearEmptiesTheList()
{
    std::cout << __func__ << std::endl;

    Collections::Generic::List<int> list;

    list.Add( 2 );
    list.Add( 4 );
    list.Add( 6 );

    assert( list.Count() == 3 );

    list.Clear();

    assert( list.Count() == 0 );
}

void Remove()
{
    std::cout << __func__ << std::endl;

    Collections::Generic::List<int> list;

    list.Add( 1 );
    list.Add( 2 );
    list.Add( 3 );
    list.Add( 1 );

    assert( list.Count() == 4 );
    assert( list[0] == 1 );
    assert( list[1] == 2 );
    assert( list[2] == 3 );
    assert( list[3] == 1 );

    // Remove the first element
    bool result = list.Remove( 1 );

    assert( result == true );
    assert( list.Count() == 3 );
    assert( list[0] == 2 );
    assert( list[1] == 3 );
    assert( list[2] == 1 );

    // Remove the last element
    result = list.Remove( 1 );

    assert( list.Count() == 2 );
    assert( result == true );
    assert( list[0] == 2 );
    assert( list[1] == 3 );

    result = list.Remove( 99 ); // Removing a non-existent item returns false

    assert( result == false );
    assert( list.Count() == 2 ); // Count() remains unchanged

    list.Add( 6 );

    assert( list.Count() == 3 );
    assert( list[0] == 2 );
    assert( list[1] == 3 );
    assert( list[2] == 6 );

    // Remove from the middle
    result = list.Remove( 3 );

    assert( list.Count() == 2 );
    assert( list[0] == 2 );
    assert( list[1] == 6 );
}

void RemoveAt()
{
    std::cout << __func__ << std::endl;

    Collections::Generic::List<int> list;

    list.Add( 2 );
    list.Add( 4 );
    list.Add( 6 );
    list.Add( 8 );
    list.Add( 10 );

    assert( list.Count() == 5 );
    assert( list[0] == 2 );
    assert( list[1] == 4 );
    assert( list[2] == 6 );
    assert( list[3] == 8 );
    assert( list[4] == 10 );

    // Remove from beginning
    list.RemoveAt( 0 );

    assert( list.Count() == 4 );
    assert( list[0] == 4 );
    assert( list[1] == 6 );
    assert( list[2] == 8 );
    assert( list[3] == 10 );

    // Remove from end
    list.RemoveAt( 3 );

    assert( list.Count() == 3 );
    assert( list[0] == 4 );
    assert( list[1] == 6 );
    assert( list[2] == 8 );

    // Remove from middle
    list.RemoveAt( 1 );

    assert( list.Count() == 2 );
    assert( list[0] == 4 );
    assert( list[1] == 8 );
}

void Contains()
{
    std::cout << __func__ << std::endl;

    // It contains the data
    {
        Collections::Generic::List<int> list;

        list.Add( 1 );

        assert( list.Contains( 1 ) );
        assert( !list.Contains( 2 ) );
    }

    // Empty list doesn't contain anything, so it doesn't contain the item...
    {
        Collections::Generic::List<int> list;

        assert( !list.Contains( 6 ) );
    }
}

void IsReadOnly()
{
    std::cout << __func__ << std::endl;

    {
        Collections::Generic::List<int> list;

        assert( !list.IsReadOnly() );
    }
    {
        const Collections::Generic::List<int> list;

        assert( list.IsReadOnly() );
    }
}

void Count()
{
    std::cout << __func__ << std::endl;

    {
        Collections::Generic::List<int> list;

        assert( list.Count() == 0 );
    }
    {
        Collections::Generic::List<int> list;

        list.Add( 2 );

        assert( list.Count() == 1 );
    }
    {
        Collections::Generic::List<int> list;

        list.Add( 2 );
        list.Add( 9 );

        assert( list.Count() == 2 );
    }
}

void ElementAccess()
{
    std::cout << __func__ << std::endl;

    {
        Collections::Generic::List<int> list;

        assert( list.Count() == 0 );
    }
    {
        Collections::Generic::List<int> list;

        list.Add( 2 );

        assert( list[0] == 2 );
    }
    {
        Collections::Generic::List<int> list;

        list.Add( 2 );
        list.Add( 9 );

        assert( list[0] == 2 );
        assert( list[1] == 9 );
    }
}

void Add()
{
    std::cout << __func__ << std::endl;

    Collections::Generic::List<int> list;

    assert( list.Count() == 0 );

    list.Add( 6 );

    assert( list.Count() == 1 );

    // Use STL to get to the underlying sequence
    assert( *list.begin() == 6 );
    assert( list[ list.Count() - 1 ] == 6 );
    assert( list.Contains( 6 ) ); // Weakest condition.  List only contains what we added.

    list.Add( 12 );

    assert( list.Count() == 2 );
    assert( list.Contains( 6 ) );
    assert( list.Contains( 12 ) );
}

void IndexOf()
{
    std::cout << __func__ << std::endl;

    std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 };
    Collections::Generic::List<int> list( a.begin(), a.end() );

    assert( list.IndexOf( 1 ) == 0 );
    assert( list.IndexOf( 2 ) == 1 );
    assert( list.IndexOf( 3 ) == 2 );
    assert( list.IndexOf( 4 ) == 3 );
    assert( list.IndexOf( 5 ) == 4 );
    assert( list.IndexOf( 6 ) == 5 );
}

void Insert()
{
    std::cout << __func__ << std::endl;

    // Insert into empty list
    {
        Collections::Generic::List<int> list;

        assert( list.Count() == 0 );

        list.Insert( 0, 6 );

        assert( list.Count() == 1 );
        assert( list[0] == 6 );
    }

    // Insert at beginning
    {
        Collections::Generic::List<int> list;

        list.Add( 6 );

        assert( list.Count() == 1 );
        assert( list[0] == 6 );

        list.Insert( 0, 3 );

        assert( list.Count() == 2 );
        assert( list[0] == 3 );
        assert( list[1] == 6 );
    }

    // Insert at end
    {
        Collections::Generic::List<int> list;

        list.Add( 6 );

        assert( list.Count() == 1 );
        assert( list[0] == 6 );

        list.Insert( 1, 3 );

        assert( list.Count() == 2 );
        assert( list[0] == 6 );
        assert( list[1] == 3 );
    }
}

System::Collections::Generic::ICollection<int> LifetimeTest()
{
    int array[] = { 1, 2, 3, 4 };
    Collections::Generic::LinkedList<int> linked_list( array );
    System::Collections::Generic::ICollection<int> collection( linked_list );

    std::cout << "Blah = " << collection.Count() << std::endl;
    return collection;
}

void GenericTest()
{
    int array[] = { 1, 2, 3, 4 };
    Collections::Generic::List<int> list( array );
    Collections::Generic::LinkedList<int> linked_list( array );
    System::Collections::Generic::ICollection<int> collection( list );
    System::Collections::Generic::ICollection<int> collection2( linked_list );
    System::Collections::Generic::ICollection<int> collection3( LifetimeTest() );

    std::cout << "Blah2 = " << collection3.Count() << std::endl;
    std::cout << "collection.Count() = " << collection.Count() << std::endl;
    std::cout << "collection2.Count() = " << collection2.Count() << std::endl;
    std::cout << "collection3.Count() = " << collection3.Count() << std::endl;
}

void TestIListInterface()
{
    std::cout << __func__ << std::endl;

    Count();
    IsReadOnly();
    ElementAccess();
    Add();
    ClearEmptiesTheList();
    Contains();
    IndexOf();
    Insert();
    Remove();
    RemoveAt();

    GenericTest();
    std::cout << "PASSED!" << std::endl;
}

void Find()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    Collections::Generic::List<int> list( a );
    Predicate<int> is_equal_to_one{ [](int item) { return item == 1; } };

    assert( list.Count() == 3 );
    assert( a[0] == 1 );
    assert( a[1] == 2 );
    assert( a[2] == 3 );

    assert( list.Find( is_equal_to_one ) == 1 );
}

template <class T>
struct Matches : Predicate<T>
{
public:
    explicit Matches(T input)
        :
        Predicate<T>( std::bind( std::equal_to<T>(), std::placeholders::_1, input ) )
    {
    }
};

void FindLast()
{
    std::cout << __func__ << std::endl;

    // Empty list won't contain the data
    {
        Collections::Generic::List<int> list;
        Matches<int> equals_one( 1 );

        assert( list.FindLast( equals_one ) == int() );
    }

    // It contains the data
    {
        Collections::Generic::List<int> list;
        Matches<int> equals_one( 1 );

        list.Add( 1 );

        assert( list.FindLast( equals_one ) == 1 );
    }

    // It contains the data
    {
        Collections::Generic::List<int> list;

        list.Add( 1 );
        list.Add( 2 );
        list.Add( 1 );

        auto ifirst = list.Find( Matches<int>( 1 ) );
        auto ilast  = list.FindLast( Matches<int>( 1 ) );

        assert( ifirst == 1 );
        assert( ilast == 1 );
    }
}

void FindAll()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    Collections::Generic::List<int> list( a );

    assert( list.FindAll( Matches<int>(1) ).Count() == 1 );
    assert( list.FindAll( Matches<int>(2) ).Count() == 2 );
    assert( list.FindAll( Matches<int>(3) ).Count() == 3 );
    assert( list.FindAll( Matches<int>(4) ).Count() == 4 );
}

void Run()
{
    std::cout << "Running List Tests..." << std::endl;

    DefaultConstructsToEmpty();
    ConstructWithExternalSequence();
    Find();
    FindLast();
    FindAll();

    TestIListInterface();

    std::cout << "PASSED!" << std::endl;
}

}
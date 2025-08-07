#include "System/Collections/Generic/LinkedList.hpp"
#include <iostream>
#include <cassert>
#include <array>


using namespace System;

namespace TestLinkedList
{

void DefaultConstructsToEmpty()
{
    Collections::Generic::LinkedList<int> empty_list;

    assert( empty_list.Count() == 0 );
}

void ConstructWithExternalSequence()
{
    // From built-in array
    {
        int a[] = { 1, 2, 3 };
        Collections::Generic::LinkedList<int> list( a );

        assert( list.Count() == 3 );
        assert( *list.Find( 1 ) == 1 );
        assert( *list.Find( 2 ) == 2 );
        assert( *list.Find( 3 ) == 3 );
    }

    // From std array
    {
        std::array<int, 3> a{ 1, 2, 3 };
        Collections::Generic::LinkedList<int> list( std::begin(a), std::end(a) );

        assert( list.Count() == 3 );
        assert( *list.Find( 1 ) == 1 );
        assert( *list.Find( 2 ) == 2 );
        assert( *list.Find( 3 ) == 3 );
    }

    // From initializer_list
    {
        Collections::Generic::LinkedList<int> list( { 1, 2, 3 } );

        assert( list.Count() == 3 );
        assert( *list.Find( 1 ) == 1 );
        assert( *list.Find( 2 ) == 2 );
        assert( *list.Find( 3 ) == 3 );
    }
}

void AddFirstAddsItemToFirstPosition()
{
    Collections::Generic::LinkedList<int> list;

    assert( list.Count() == 0 );

    list.AddFirst( 6 );

    assert( list.Count() == 1 );

    // Use STL to get to the underlying sequence
    assert( *list.begin() == 6 );

    list.AddFirst( 12 );

    assert( list.Count() == 2 );

    {
        Collections::Generic::LinkedList<int>::iterator iIter( list.begin() );

        assert( *iIter == 12 );

        ++iIter;

        assert( *iIter == 6 );
    }
}

void AddLastAddsItemToLastPosition()
{
    Collections::Generic::LinkedList<int> list;

    assert( list.Count() == 0 );

    list.AddLast( 6 );

    assert( list.Count() == 1 );

    // Use STL to get to the underlying sequence
    assert( *list.begin() == 6 );

    list.AddLast( 12 );

    assert( list.Count() == 2 );

    {
        Collections::Generic::LinkedList<int>::iterator iIter( list.begin() );

        assert( *iIter == 6 );

        ++iIter;

        assert( *iIter == 12 );
    }
}

void ClearEmptiesTheList()
{
    Collections::Generic::LinkedList<int> list;

    list.AddFirst( 2 );
    list.AddFirst( 4 );
    list.AddFirst( 6 );

    assert( list.Count() == 3 );

    list.Clear();

    assert( list.Count() == 0 );
}

void RemoveFirstRemovesTheFirstItem()
{
    Collections::Generic::LinkedList<int> list;

    list.AddFirst( 2 );
    list.AddFirst( 4 );
    list.AddFirst( 6 );

    assert( list.Count() == 3 );

    assert( *std::next( list.begin(), 0 ) == 6 );
    assert( *std::next( list.begin(), 1 ) == 4 );
    assert( *std::next( list.begin(), 2 ) == 2 );

    list.RemoveFirst();

    assert( list.Count() == 2 );

    assert( *std::next( list.begin(), 0 ) == 4 );
    assert( *std::next( list.begin(), 1 ) == 2 );

    list.RemoveFirst();

    assert( list.Count() == 1 );

    assert( *std::next( list.begin(), 0 ) == 2 );

    list.RemoveFirst();

    assert( list.Count() == 0 );
}

void RemoveLastRemovesTheLastItem()
{
    Collections::Generic::LinkedList<int> list;

    list.AddFirst( 2 );
    list.AddFirst( 4 );
    list.AddFirst( 6 );

    assert( list.Count() == 3 );

    assert( *std::next( list.begin(), 0 ) == 6 );
    assert( *std::next( list.begin(), 1 ) == 4 );
    assert( *std::next( list.begin(), 2 ) == 2 );

    list.RemoveLast();

    assert( list.Count() == 2 );

    assert( *std::next( list.begin(), 0 ) == 6 );
    assert( *std::next( list.begin(), 1 ) == 4 );

    list.RemoveLast();

    assert( list.Count() == 1 );

    assert( *list.begin() == 6 );

    list.RemoveFirst();

    assert( list.Count() == 0 );
}

void IsSynchronized()
{
    Collections::Generic::LinkedList<int> list;

    assert( !list.IsSynchronized() );
}

void IsReadOnly()
{
    {
        Collections::Generic::LinkedList<int> list;

        assert( !list.IsReadOnly() );
    }
    {
        const Collections::Generic::LinkedList<int> list;

        assert( list.IsReadOnly() );
    }
}

void RemoveRemovesTheFirstFoundItem()
{
    Collections::Generic::LinkedList<int> list;

    list.AddLast( 1 );
    list.AddLast( 2 );
    list.AddLast( 3 );
    list.AddLast( 1 );

    assert( list.Count() == 4 );

    bool result = list.Remove( 1 );

    assert( result == true );
    assert( list.Count() == 3 );

    result = list.Remove( 1 );

    assert( list.Count() == 2 );
    assert( result == true );

    result = list.Remove( 99 ); // Removing a non-existent item returns false

    assert( result == false );
}

void Contains()
{
    // It contains the data
    {
        Collections::Generic::LinkedList<int> list;

        list.AddLast( 1 );

        assert( list.Contains( 1 ) );
        assert( !list.Contains( 2 ) );
    }

    // Empty list doesn't contain anything, so it doesn't contain the item...
    {
        Collections::Generic::LinkedList<int> list;

        assert( !list.Contains( 6 ) );
    }
}

void Find()
{
    // Empty list won't contain the data
    {
        Collections::Generic::LinkedList<int> list;

        assert( list.Find( 3 ) == list.end() );
    }

    // It contains the data
    {
        Collections::Generic::LinkedList<int> list;

        list.AddLast( 1 );

        assert( list.Find( 1 ) != list.end() );
        assert( *list.Find( 1 ) == 1 );
        assert( std::distance( list.begin(), list.Find( 1 ) ) == 0 );
    }
}

void FindLast()
{
    // Empty list won't contain the data
    {
        Collections::Generic::LinkedList<int> list;

        assert( list.FindLast( 3 ) == list.end() );
    }

    // It contains the data
    {
        Collections::Generic::LinkedList<int> list;

        list.AddLast( 1 );

        assert( std::distance( list.begin(), list.FindLast( 1 ) ) == 0 );
        assert( *list.FindLast( 1 ) == 1 );
    }

    // It contains the data
    {
        Collections::Generic::LinkedList<int> list;

        list.AddLast( 1 );
        list.AddLast( 2 );
        list.AddLast( 1 );

        auto ifirst = list.Find( 1 );
        auto ilast  = list.FindLast( 1 );

        assert( *ifirst == 1 );
        assert( *ilast == 1 );
        assert( ifirst != ilast );
        assert( std::distance( list.begin(), ifirst ) == 0 );
        assert( std::distance( list.begin(), ilast ) == 2 );
    }
}

void Run()
{
    DefaultConstructsToEmpty();
    ConstructWithExternalSequence();
    AddFirstAddsItemToFirstPosition();
    AddLastAddsItemToLastPosition();
    RemoveFirstRemovesTheFirstItem();
    RemoveLastRemovesTheLastItem();
    IsSynchronized();
    IsReadOnly();
    RemoveRemovesTheFirstFoundItem();
    Contains();
    Find();
    FindLast();
}

}

int main(void)
{
    TestLinkedList::Run();

    return EXIT_SUCCESS;
}
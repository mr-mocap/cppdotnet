#include "System/Collections/Generic/Stack.hpp"
#include <iostream>
#include <cassert>


namespace TestStack
{

void DefaultConstructed()
{
    System::Collections::Generic::Stack<int> default_constructed;

    assert( default_constructed.Count() == 0 );
    //assert( default_constructed.Capacity() == ? );
}

void PushIncreasesTheCountByOne()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    stack.Push(10);

    assert( stack.Count() == 1 );
}

void PushAddsTheItemToTheTop()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    stack.Push(10);

    assert( stack.Count() == 1 );
    assert( stack.Peek() == 10 );
}

void PeekReturnsTheObjectAtTheTopOfTheStackWithoutRemovingIt()
{
    System::Collections::Generic::Stack<int> stack;

    stack.Push(10);

    assert( stack.Count() == 1 );
    assert( stack.Peek() == 10 );
    assert( stack.Count() == 1 );
}

void PopRemovesAndReturnsTheTopItem()
{
    System::Collections::Generic::Stack<int> stack;

    stack.Push(10);

    assert( stack.Count() == 1 );
    assert( stack.Peek() == 10 );

    int top_item = stack.Pop();

    assert( top_item == 10 );
    assert( stack.Count() == 0 );
}

void PoppingAnEmptyStackThrowsAnException()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    try
    {
        int top_item = stack.Pop();

        UNUSED(top_item);
        assert( false );
    }
    catch(const System::InvalidOperationException &e)
    {
        std::cout << e.ToString() << std::endl;
    }
    
    assert( stack.Count() == 0 );
}

void PeekingAnEmptyStackThrowsAnException()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    try
    {
        int top_item = stack.Peek();

        UNUSED(top_item);
        assert( false );
    }
    catch(const System::InvalidOperationException &e)
    {
        std::cout << e.ToString() << std::endl;
    }
    
    assert( stack.Count() == 0 );
}

void ContainsReturnsTrueWhenTheItemIsInTheStack()
{
    System::Collections::Generic::Stack<int> stack;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    assert( stack.Count() == 3 );
    assert( stack.Contains( 20 ) );
}

void TryPeekReturnsTrueAndCopiesValueToOutputParameter()
{
    System::Collections::Generic::Stack<int> stack;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    assert( stack.Count() == 3 );

    int peeked_value = -1;

    assert( stack.TryPeek(peeked_value) );
    assert( stack.Count() == 3 );
    assert( peeked_value == 30 );
}

void TryPeekReturnsFalseWhenStackIsEmpty()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    int peeked_value = -1;

    assert( !stack.TryPeek(peeked_value) );
    assert( stack.Count() == 0 );
    assert( peeked_value == 0 );
}

void TryPopReturnsTrueAndCopiesValueToOutputParameter()
{
    System::Collections::Generic::Stack<int> stack;

    stack.Push(30);

    assert( stack.Count() == 1 );

    int popped_value = -1;

    assert( stack.TryPop(popped_value) );
    assert( stack.Count() == 0 );
    assert( popped_value == 30 );
}

void TryPopReturnsFalseWhenStackIsEmpty()
{
    System::Collections::Generic::Stack<int> stack;

    assert( stack.Count() == 0 );

    int popped_value = -1;

    assert( !stack.TryPop(popped_value) );
    assert( stack.Count() == 0 );
    assert( popped_value == 0 );
}

void Run()
{
    std::cout << "Running Version Tests..." << std::endl;

    DefaultConstructed();
    PushIncreasesTheCountByOne();
    PushAddsTheItemToTheTop();
    PeekReturnsTheObjectAtTheTopOfTheStackWithoutRemovingIt();
    PopRemovesAndReturnsTheTopItem();
    PoppingAnEmptyStackThrowsAnException();
    PeekingAnEmptyStackThrowsAnException();
    ContainsReturnsTrueWhenTheItemIsInTheStack();
    TryPeekReturnsTrueAndCopiesValueToOutputParameter();
    TryPeekReturnsFalseWhenStackIsEmpty();
    TryPopReturnsTrueAndCopiesValueToOutputParameter();
    TryPopReturnsFalseWhenStackIsEmpty();
}

}

int main(void)
{
    TestStack::Run();

    return EXIT_SUCCESS;
}